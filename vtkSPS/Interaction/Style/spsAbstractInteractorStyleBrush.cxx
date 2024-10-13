#include <vtkIdTypeArray.h>
#include <vtkMatrix4x4.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPointLocator.h>
#include <vtkPointPicker.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkStaticPointLocator.h>
#include <vtkTransform.h>
#include <vtkUnsignedCharArray.h>

#include <spsInteractorStyleDemo.h>

//------------------------------------------------------------------------------
spsAbstractInteractorStyleBrush::spsAbstractInteractorStyleBrush()
{
  this->BrushRadius = 5.0; // Default brush radius
  this->Resolution = 10;
  this->UseStaticLocators = true;
  this->IsActive = false;
  this->CurrentActor = nullptr;
  this->CurrentPointId = -1;
  this->CurrentLocalPosition[0] = this->CurrentLocalPosition[1] = this->CurrentLocalPosition[2] =
    0.0;
  this->LastLocalPosition[0] = this->LastLocalPosition[1] = this->LastLocalPosition[2] = 0.0;
}

spsAbstractInteractorStyleBrush::~spsAbstractInteractorStyleBrush() {}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "BrushRadius: " << this->BrushRadius << "\n";
  os << indent << "Resolution: " << this->Resolution << "\n";
  os << indent << "UseStaticLocators: " << this->UseStaticLocators << "\n";
  os << indent << "CurrentLocalPosition: [ " << this->CurrentLocalPosition[0] << ", "
     << this->CurrentLocalPosition[1] << ", " << this->CurrentLocalPosition[2] << " ]\n";
  os << indent << "LastLocalPosition: [ " << this->LastLocalPosition[0] << ", "
     << this->LastLocalPosition[1] << ", " << this->LastLocalPosition[2] << " ]\n";
  Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::TransformToLocalCoordinates(
  vtkActor* actor, const double worldPosition[3], double localPosition[3])
{
  // Get the actor's transformation matrix
  vtkNew<vtkMatrix4x4> actorMatrix;
  actor->GetMatrix(actorMatrix);

  // Invert the matrix to convert world coordinates to local coordinates
  vtkNew<vtkMatrix4x4> invertedMatrix;
  invertedMatrix->DeepCopy(actorMatrix);
  invertedMatrix->Invert();

  // Create a transform and apply the inverted matrix
  vtkNew<vtkTransform> inverseTransform;
  inverseTransform->SetMatrix(invertedMatrix);

  // Apply the inverse transform to the world position to get the local position
  inverseTransform->TransformPoint(worldPosition, localPosition);
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::OnLeftButtonDown()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
  double currentPosition[3];
  if (!renderer)
  {
    return;
  }

  int* mousePos = this->GetInteractor()->GetEventPosition();

  // Use vtkCellPicker to pick the actor under the mouse position
  this->Picker->Pick(mousePos[0], mousePos[1], 0, renderer);
  this->CurrentActor = this->Picker->GetActor();

  if (this->CurrentActor)
  {
    vtkPolyData* polyData = vtkPolyData::SafeDownCast(this->CurrentActor->GetMapper()->GetInput());
    if (polyData)
    {
      this->Picker->GetPickPosition(currentPosition);
      this->TransformToLocalCoordinates(
        this->CurrentActor, currentPosition, this->CurrentLocalPosition);

      // Save the current position as the potential brush application point
      this->LastLocalPosition[0] = this->CurrentLocalPosition[0];
      this->LastLocalPosition[1] = this->CurrentLocalPosition[1];
      this->LastLocalPosition[2] = this->CurrentLocalPosition[2];

      // Apply brush effect at the current point
      this->ApplyBrush(this->CurrentActor, polyData);

      this->IsActive = true; // Set active only if we hit something
    }
  }

  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::OnMouseMove()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = nullptr;
  vtkPolyData* polyData = nullptr;
  double currentPosition[3];

  renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
  if (!renderer)
  {
    return;
  }

  if (!this->IsActive)
  {
    // Don't paint unless the left mouse button is pressed
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return;
  }

  int* mousePos = this->GetInteractor()->GetEventPosition();

  // Use vtkCellPicker to pick the actor under the mouse position
  this->Picker->Pick(mousePos[0], mousePos[1], 0, renderer);
  this->CurrentActor = this->Picker->GetActor();

  if (this->CurrentActor)
  {
    polyData = vtkPolyData::SafeDownCast(this->CurrentActor->GetMapper()->GetInput());
  }

  if (!this->CurrentActor || !polyData)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for null actor
  }

  this->CurrentPointId = this->Picker->GetPointId();
  if (this->CurrentPointId < 0)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for invalid point ID
  }

  this->Picker->GetPickPosition(currentPosition);

  // Transform the world position to local coordinates
  this->TransformToLocalCoordinates(
    this->CurrentActor, currentPosition, this->CurrentLocalPosition);

  // Calculate the distance between the last applied position and the current position
  double distanceSquared =
    vtkMath::Distance2BetweenPoints(this->LastLocalPosition, this->CurrentLocalPosition);

  double BrushApplicationThreshold = this->BrushRadius / double(this->Resolution);
  // Apply the brush only if the distance is greater than or equal to 1/10th of the brush radius
  if (distanceSquared >= (BrushApplicationThreshold * BrushApplicationThreshold))
  {
    // Apply brush effect at the current point
    this->ApplyBrush(this->CurrentActor, polyData);

    // Update the last applied position
    this->LastLocalPosition[0] = this->CurrentLocalPosition[0];
    this->LastLocalPosition[1] = this->CurrentLocalPosition[1];
    this->LastLocalPosition[2] = this->CurrentLocalPosition[2];
  }
  this->IsActive = true;
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::OnLeftButtonUp()
{
  vtkDebugMacro("" << __FUNCTION__);

  if (this->IsActive && this->CurrentActor)
  {
    // We IsActive to false and then current position is brushed
    this->IsActive = false;
    vtkPolyData* polyData = vtkPolyData::SafeDownCast(this->CurrentActor->GetMapper()->GetInput());
    if (polyData)
    {
      // Apply brush effect at the last picked position
      this->ApplyBrush(this->CurrentActor, polyData);
    }
  }
  // Reset states
  this->IsActive = false;
  this->CurrentActor = nullptr;
  vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::SetUseStaticLocators(bool polyDataStatic)
{
  if (this->UseStaticLocators == polyDataStatic)
  {
    return;
  }
  this->UseStaticLocators = polyDataStatic;
  for (auto& entry : this->LocatorMap)
  {
    vtkSmartPointer<vtkActor> actor = entry.first;

    vtkDataSet* dataSet = entry.second->GetDataSet();

    if (this->UseStaticLocators)
    {
      vtkSmartPointer<vtkStaticPointLocator> staticLocator =
        vtkSmartPointer<vtkStaticPointLocator>::New();
      staticLocator->SetDataSet(dataSet);
      staticLocator->BuildLocator();
      entry.second = staticLocator;
    }
    else
    {
      vtkSmartPointer<vtkPointLocator> pointLocator = vtkSmartPointer<vtkPointLocator>::New();
      pointLocator->SetDataSet(dataSet);
      pointLocator->BuildLocator();
      entry.second = pointLocator;
    }
  }
  this->Modified();
}

//------------------------------------------------------------------------------
vtkSmartPointer<vtkAbstractPointLocator> spsAbstractInteractorStyleBrush::GetLocator(
  vtkActor* actor, vtkPolyData* polyData)
{
  vtkSmartPointer<vtkAbstractPointLocator> pointLocator;

  vtkSmartPointer<vtkActor> smartActor = vtkSmartPointer<vtkActor>(actor);

  // Check if a locator already exists for this actor
  if (LocatorMap.find(smartActor) == LocatorMap.end())
  {
    // Create a new locator and store it
    if (this->UseStaticLocators)
    {
      pointLocator = vtkSmartPointer<vtkStaticPointLocator>::New();
    }
    else
    {
      pointLocator = vtkSmartPointer<vtkPointLocator>::New();
    }
    pointLocator->SetDataSet(polyData);
    pointLocator->BuildLocator();
    LocatorMap[smartActor] = pointLocator;
  }
  else
  {
    pointLocator = LocatorMap[smartActor];
  }
  return pointLocator;
}
