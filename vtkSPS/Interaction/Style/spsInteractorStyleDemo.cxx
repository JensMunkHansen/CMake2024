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

namespace
{
//------------------------------------------------------------------------------
bool ActorHasColors(vtkActor* actor)
{
  vtkPolyData* polyData = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput());
  if (polyData && polyData->GetPointData()->GetScalars())
  {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void AddInitialColor(vtkActor* actor, vtkPolyData* polyData)
{
  vtkNew<vtkUnsignedCharArray> colors;
  colors->SetNumberOfComponents(3);
  colors->SetNumberOfTuples(polyData->GetNumberOfPoints());
  colors->SetName("Colors");

  const uint8_t newColor[3] = { 255, 255, 255 };
  for (vtkIdType i = 0; i < polyData->GetNumberOfPoints(); ++i)
  {
    colors->SetTypedTuple(i, newColor);
  }

  polyData->GetPointData()->SetScalars(colors);
  actor->GetMapper()->Update();
}
} // namespace

vtkStandardNewMacro(spsInteractorStyleDemo);

//------------------------------------------------------------------------------
spsInteractorStyleDemo::spsInteractorStyleDemo()
{
  this->BrushRadius = 5.0; // Default brush radius
  this->Resolution = 10;
  this->UseStaticLocators = true;
  this->IsActive = false;
  this->IsFirst = true;
  this->CurrentActor = nullptr;
  this->CurrentPointId = -1;
  this->CurrentPosition[0] = this->CurrentPosition[1] = this->CurrentPosition[2] = 0.0;
  this->CurrentLocalPosition[0] = this->CurrentLocalPosition[1] = this->CurrentLocalPosition[2] =
    0.0;
  this->LastLocalPosition[0] = this->LastLocalPosition[1] = this->LastLocalPosition[2] = 0.0;
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "BrushRadius: " << this->BrushRadius << "\n";
  os << indent << "Resolution: " << this->Resolution << "\n";
  os << indent << "UseStaticLocators: " << this->UseStaticLocators << "\n";
  os << indent << "CurrentPosition: [ " << this->CurrentPosition[0] << ", "
     << this->CurrentPosition[1] << ", " << this->CurrentPosition[2] << " ]\n";
  os << indent << "CurrentLocalPosition: [ " << this->CurrentLocalPosition[0] << ", "
     << this->CurrentLocalPosition[1] << ", " << this->CurrentLocalPosition[2] << " ]\n";
  os << indent << "LastLocalPosition: [ " << this->LastLocalPosition[0] << ", "
     << this->LastLocalPosition[1] << ", " << this->LastLocalPosition[2] << " ]\n";
  Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::TransformToLocalCoordinates(
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
void spsInteractorStyleDemo::OnLeftButtonDown()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

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
      this->Picker->GetPickPosition(this->CurrentPosition);
      this->TransformToLocalCoordinates(
        this->CurrentActor, this->CurrentPosition, this->CurrentLocalPosition);

      // Save the current position as the potential brush application point
      this->LastLocalPosition[0] = this->CurrentLocalPosition[0];
      this->LastLocalPosition[1] = this->CurrentLocalPosition[1];
      this->LastLocalPosition[2] = this->CurrentLocalPosition[2];

      this->Counter = 0;
      this->IsActive = true; // Set active only if we hit something
      this->IsFirst = true;
    }
  }

  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::OnMouseMove()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = nullptr;
  vtkPolyData* polyData = nullptr;

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

  this->Picker->GetPickPosition(this->CurrentPosition);

  // Transform the world position to local coordinates
  this->TransformToLocalCoordinates(
    this->CurrentActor, this->CurrentPosition, this->CurrentLocalPosition);

  // Calculate the distance between the last applied position and the current position
  double distanceSquared =
    vtkMath::Distance2BetweenPoints(this->LastLocalPosition, this->CurrentLocalPosition);

  double BrushApplicationThreshold = this->BrushRadius / double(this->Resolution);
  // Apply the brush only if the distance is greater than or equal to 1/10th of the brush radius
  if (distanceSquared >= (BrushApplicationThreshold * BrushApplicationThreshold) || this->IsFirst)
  {
    // Apply brush effect at the current point
    this->ApplyBrush(this->CurrentActor, polyData);

    // Update the last applied position
    this->LastLocalPosition[0] = this->CurrentLocalPosition[0];
    this->LastLocalPosition[1] = this->CurrentLocalPosition[1];
    this->LastLocalPosition[2] = this->CurrentLocalPosition[2];
    this->Counter++;
    this->IsFirst = false;
  }
  this->IsActive = true;
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::OnLeftButtonUp()
{
  vtkDebugMacro("" << __FUNCTION__);

  if (this->IsActive && this->CurrentActor)
  {
    vtkPolyData* polyData = vtkPolyData::SafeDownCast(this->CurrentActor->GetMapper()->GetInput());
    if (polyData)
    {
      // Apply brush effect at the last picked position
      this->ApplyBrush(this->CurrentActor, polyData);
      this->Counter++;
    }
  }
  // Reset states
  this->IsActive = false;
  this->IsFirst = false;
  this->CurrentActor = nullptr;
  vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::SetUseStaticLocators(bool polyDataStatic)
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
vtkSmartPointer<vtkAbstractPointLocator> spsInteractorStyleDemo::GetLocator(
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

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::ApplyBrush(vtkActor* actor, vtkPolyData* polyData)
{
  vtkDebugMacro("" << __FUNCTION__);

  if (!ActorHasColors(actor))
  {
    AddInitialColor(actor, polyData);
  }

  vtkSmartPointer<vtkAbstractPointLocator> pointLocator = this->GetLocator(actor, polyData);

  // Find points within the brush radius
  vtkNew<vtkIdList> result;

  pointLocator->FindPointsWithinRadius(BrushRadius, this->CurrentLocalPosition, result);

  vtkUnsignedCharArray* colors =
    vtkUnsignedCharArray::SafeDownCast(polyData->GetPointData()->GetScalars());
  if (!colors)
  {
    return;
  }

  const uint8_t newColor[3] = { 255, 0, 0 };
  // Set the selected points to red color
  for (vtkIdType i = 0; i < result->GetNumberOfIds(); ++i)
  {
    vtkIdType id = result->GetId(i);
    colors->SetTypedTuple(id, newColor);
  }

  if (result->GetNumberOfIds() > 0)
  {
    polyData->GetPointData()->Modified();
    this->Interactor->GetRenderWindow()->Render();
  }
}
