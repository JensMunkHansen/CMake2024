#include "spsAbstractInteractorStyleBrush.h"
#include <spsInteractorStyleDemo.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkMatrix4x4.h>
#include <vtkObjectFactory.h>
#include <vtkOctreePointLocator.h>
#include <vtkPicker.h>
#include <vtkPointData.h>
#include <vtkPointLocator.h>
#include <vtkPointPicker.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPropPicker.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSmartPointer.h>
#include <vtkStaticPointLocator.h>
#include <vtkTransform.h>
#include <vtkUnsignedCharArray.h>
#include <vtkWorldPointPicker.h>

namespace
{

// Works for vtkWorldPointPicker
vtkActor* PickerGetActor(
  vtkAbstractPicker* picker, vtkRenderer* renderer, double pickedWorldPoint[3])
{

  // Loop through the actors in the renderer
  vtkActorCollection* actors = renderer->GetActors();
  vtkActor* pickedActor = nullptr;

  actors->InitTraversal();
  vtkActor* actor = nullptr;
  while ((actor = actors->GetNextActor()))
  {
    // Get the bounding box of the actor
    double bounds[6];
    actor->GetBounds(bounds);

    // Check if the picked world point is within the bounds of the actor
    if ((pickedWorldPoint[0] >= bounds[0] && pickedWorldPoint[0] <= bounds[1]) &&
      (pickedWorldPoint[1] >= bounds[2] && pickedWorldPoint[1] <= bounds[3]) &&
      (pickedWorldPoint[2] >= bounds[4] && pickedWorldPoint[2] <= bounds[5]))
    {
      pickedActor = actor;
      break;
    }
  }
  return pickedActor;
}

}
//------------------------------------------------------------------------------
spsAbstractInteractorStyleBrush::spsAbstractInteractorStyleBrush()
{
  this->BrushRadius = 5.0; // Default brush radius
  this->Resolution = 10;
  this->IsActive = false;
  this->CurrentActor = nullptr;
  this->CurrentLocalPosition[0] = this->CurrentLocalPosition[1] = this->CurrentLocalPosition[2] =
    0.0;
  this->LastLocalPosition[0] = this->LastLocalPosition[1] = this->LastLocalPosition[2] = 0.0;
  //  this->Picker = vtkSmartPointer<vtkCellPicker>::New();
  // this->Picker = vtkSmartPointer<vtkPropPicker>::New(); // Not working
  this->Picker = vtkSmartPointer<vtkPointPicker>::New();
}

//------------------------------------------------------------------------------
spsAbstractInteractorStyleBrush::~spsAbstractInteractorStyleBrush() {}

//------------------------------------------------------------------------------
const char* spsAbstractInteractorStyleBrush::GetLocatorModeAsString()
{
  if (this->LocatorMode == spsAbstractInteractorStyleBrush::PointLocator)
  {
    return "PointLocator";
  }
  if (this->LocatorMode == spsAbstractInteractorStyleBrush::StaticPointLocator)
  {
    return "StaticPointLocator";
  }
  else
  {
    return "OctreePointLocator";
  }
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "BrushRadius: " << this->BrushRadius << "\n";
  os << indent << "Resolution: " << this->Resolution << "\n";
  os << indent << "LocatorMode: " << this->GetLocatorModeAsString() << "\n";
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
  vtkMatrix4x4::Invert(actorMatrix, invertedMatrix);

  // Create a transform and apply the inverted matrix
  vtkNew<vtkTransform> inverseTransform;
  inverseTransform->SetMatrix(invertedMatrix);

  // Apply the inverse transform to the world position to get the local position
  inverseTransform->TransformPoint(worldPosition, localPosition);
}

void spsAbstractInteractorStyleBrush::UpdateActorToLocalTransform()
{
  // Get the actor's transformation matrix
  vtkNew<vtkMatrix4x4> actorMatrix;
  this->CurrentActor->GetMatrix(actorMatrix);

  // Invert the matrix to convert world coordinates to local coordinates
  vtkNew<vtkMatrix4x4> invertedMatrix;
  vtkMatrix4x4::Invert(actorMatrix, invertedMatrix);

  this->ActorToLocalTransform->SetMatrix(invertedMatrix);
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

  vtkActor* actor = nullptr;

  vtkSmartPointer<vtkPicker> picker = vtkPicker::SafeDownCast(this->Picker);

  if (picker)
  {
    actor = picker->GetActor();

    if (actor)
    {
      vtkPolyData* polyData = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput());
      if (polyData)
      {
        this->Picker->GetPickPosition(currentPosition);

        if (actor != this->CurrentActor)
        {
          this->CurrentActor = actor;
          this->UpdateActorToLocalTransform();
        }
        this->ActorToLocalTransform->TransformPoint(currentPosition, this->CurrentLocalPosition);

        // Save the current position as the potential brush application point
        this->LastLocalPosition[0] = this->CurrentLocalPosition[0];
        this->LastLocalPosition[1] = this->CurrentLocalPosition[1];
        this->LastLocalPosition[2] = this->CurrentLocalPosition[2];

        // Apply brush effect at the current point
        this->ApplyBrush(this->CurrentActor, polyData);

        this->IsActive = true; // Set active only if we hit something
      }
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

  vtkActor* actor = nullptr;

  vtkSmartPointer<vtkPicker> picker = vtkPicker::SafeDownCast(this->Picker);

  if (picker)
  {
    actor = picker->GetActor();
  }

  if (actor)
  {
    polyData = vtkPolyData::SafeDownCast(this->CurrentActor->GetMapper()->GetInput());
  }

  if (!actor || !polyData)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for null actor
  }

  if (actor != this->CurrentActor)
  {
    this->CurrentActor = actor;
    this->UpdateActorToLocalTransform();
  }

  this->Picker->GetPickPosition(currentPosition);

  // Transform the world position to local coordinates
  this->ActorToLocalTransform->TransformPoint(currentPosition, this->CurrentLocalPosition);

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
  this->RemoveUnusedLocators();
  vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------------
void spsAbstractInteractorStyleBrush::SetLocatorMode(int locatorMode)
{
  if (this->LocatorMode == locatorMode)
  {
    return;
  }
  if (locatorMode < spsAbstractInteractorStyleBrush::OctreePointLocator)
    locatorMode = spsAbstractInteractorStyleBrush::OctreePointLocator;
  if (locatorMode > spsAbstractInteractorStyleBrush::StaticPointLocator)
    locatorMode = spsAbstractInteractorStyleBrush::StaticPointLocator;

  this->LocatorMode = locatorMode;

  for (auto& entry : this->LocatorMap)
  {
    vtkSmartPointer<vtkActor> actor = entry.first;

    vtkDataSet* dataSet = entry.second->GetDataSet();

    vtkSmartPointer<vtkAbstractPointLocator> locator = nullptr;

    switch (this->LocatorMode)
    {
      case spsAbstractInteractorStyleBrush::OctreePointLocator:
        locator = vtkSmartPointer<vtkOctreePointLocator>::New();
        locator->SetDataSet(dataSet);
        locator->BuildLocator();
        entry.second = locator;
        break;
      case spsAbstractInteractorStyleBrush::StaticPointLocator:
        locator = vtkSmartPointer<vtkStaticPointLocator>::New();
        locator->SetDataSet(dataSet);
        locator->BuildLocator();
        entry.second = locator;
        break;
      case spsAbstractInteractorStyleBrush::PointLocator:
      default:
        locator = vtkSmartPointer<vtkPointLocator>::New();
        locator->SetDataSet(dataSet);
        locator->BuildLocator();
        entry.second = locator;
        break;
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
    switch (this->LocatorMode)
    {
      case spsAbstractInteractorStyleBrush::OctreePointLocator:
        pointLocator = vtkSmartPointer<vtkOctreePointLocator>::New();
        break;
      case spsAbstractInteractorStyleBrush::StaticPointLocator:
        pointLocator = vtkSmartPointer<vtkStaticPointLocator>::New();
        break;
      case spsAbstractInteractorStyleBrush::PointLocator:
      default:
        pointLocator = vtkSmartPointer<vtkPointLocator>::New();
        break;
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
void spsAbstractInteractorStyleBrush::RemoveUnusedLocators()
{
  vtkRenderer* renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

  if (renderer)
  {
    for (auto& entry : this->LocatorMap)
    {
      if (!renderer->HasViewProp(entry.first))
      {
        this->LocatorMap.erase(entry.first);
      }
    }
  }
}

#if 0

#endif
