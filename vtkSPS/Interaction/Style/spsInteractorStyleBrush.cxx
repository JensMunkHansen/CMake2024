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

#include <spsInteractorStyleBrush.h>

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

vtkStandardNewMacro(spsInteractorStyleBrush);

//------------------------------------------------------------------------------
spsInteractorStyleBrush::spsInteractorStyleBrush()
{
  this->BrushRadius = 5.0; // Default brush radius
  this->UseStaticLocators = true;
  this->IsActive = false;
  this->CurrentActor = nullptr;
  this->CurrentPointId = -1;
  this->CurrentPosition[0] = this->CurrentPosition[1] = this->CurrentPosition[2] = 0.0;
  this->CurrentLocalPosition[0] = this->CurrentLocalPosition[1] = this->CurrentLocalPosition[2] =
    0.0;
  this->LastLocalPosition[0] = this->LastLocalPosition[1] = this->LastLocalPosition[2] = 0.0;
}

void spsInteractorStyleBrush::TransformToLocalCoordinates(
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
void spsInteractorStyleBrush::OnLeftButtonDown()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

  if (!renderer)
  {
    return;
  }

  this->IsActive = true; // Start painting when the left mouse button is pressed
  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

//------------------------------------------------------------------------------
void spsInteractorStyleBrush::OnLeftButtonUp()
{
  vtkDebugMacro("" << __FUNCTION__);
  this->IsActive = false; // Stop painting when the left mouse button is released
  vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------------
void spsInteractorStyleBrush::SetUseStaticLocators(bool polyDataStatic)
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
void spsInteractorStyleBrush::OnMouseMove()
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

  // Apply brush effect at the current point
  this->ApplyBrush(this->CurrentActor, polyData);
}

vtkSmartPointer<vtkAbstractPointLocator> spsInteractorStyleBrush::GetLocator(
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
void spsInteractorStyleBrush::ApplyBrush(vtkActor* actor, vtkPolyData* polyData)
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
