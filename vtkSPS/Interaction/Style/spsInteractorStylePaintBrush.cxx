#include <vtkActor.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkObjectFactory.h>
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
#include <vtkSetGet.h>
#include <vtkSmartPointer.h>
#include <vtkUnsignedCharArray.h>

#include <spsInteractorStylePaintBrush.h>

vtkStandardNewMacro(spsInteractorStylePaintBrush);

//------------------------------------------------------------------------------
spsInteractorStylePaintBrush::spsInteractorStylePaintBrush()
{
  this->BrushRadius = 5.0; // Default brush radius
  this->IsActive = false;
  //  this->Picker = vtkSmartPointer<vtkCellPicker>::New();

  // If data doesn't change use instead vtkStaticPointLocator
  this->Picker = vtkSmartPointer<vtkPointPicker>::New();
  // Question: StaticPointPicker, SurfacePointPlacer.... Can this be made faster
}

//------------------------------------------------------------------------------
void spsInteractorStylePaintBrush::OnLeftButtonDown()
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
void spsInteractorStylePaintBrush::OnLeftButtonUp()
{
  vtkDebugMacro("" << __FUNCTION__);
  this->IsActive = false; // Stop painting when the left mouse button is released
  vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

//------------------------------------------------------------------------------
void spsInteractorStylePaintBrush::OnMouseMove()
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkRenderer* renderer = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
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
  Picker->Pick(mousePos[0], mousePos[1], 0, renderer);

  vtkActor* actor = Picker->GetActor();
  if (!actor)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for null actor
  }

  vtkPolyData* polyData = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput());
  if (!polyData)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for null polyData
  }

  if (!ActorHasColors(actor))
  {
    AddInitialColor(actor, polyData);
  }

  vtkIdType pickedPointId = Picker->GetPointId();
  if (pickedPointId < 0)
  {
    vtkInteractorStyleTrackballCamera::OnMouseMove();
    return; // Safety check for invalid point ID
  }

  // Apply brush effect at the current point
  ApplyBrush(actor, polyData, pickedPointId);
}

//------------------------------------------------------------------------------
bool spsInteractorStylePaintBrush::ActorHasColors(vtkActor* actor)
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkPolyData* polyData = vtkPolyData::SafeDownCast(actor->GetMapper()->GetInput());
  if (polyData && polyData->GetPointData()->GetScalars())
  {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void spsInteractorStylePaintBrush::AddInitialColor(vtkActor* actor, vtkPolyData* polyData)
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkNew<vtkUnsignedCharArray> colors;
  colors->SetNumberOfComponents(3);
  colors->SetNumberOfTuples(polyData->GetNumberOfPoints());

  const uint8_t newColor[3] = { 255, 255, 255 };
  for (vtkIdType i = 0; i < polyData->GetNumberOfPoints(); ++i)
  {
    colors->SetTypedTuple(i, newColor);
  }

  polyData->GetPointData()->SetScalars(colors);
  actor->GetMapper()->Update();
}

//------------------------------------------------------------------------------
void spsInteractorStylePaintBrush::ApplyBrush(
  vtkActor* actor, vtkPolyData* polyData, vtkIdType pointId)
{
  vtkDebugMacro("" << __FUNCTION__);
  vtkSmartPointer<vtkPointLocator> pointLocator;

  // Check if a locator already exists for this actor
  if (LocatorMap.find(actor) == LocatorMap.end())
  {
    // Create a new locator and store it
    pointLocator = vtkSmartPointer<vtkPointLocator>::New();
    pointLocator->SetDataSet(polyData);
    pointLocator->BuildLocator();
    LocatorMap[actor] = pointLocator;
  }
  else
  {
    pointLocator = LocatorMap[actor];
  }

  // TODO: Print both the GetPoint and the point using the other wa

  // Find points within the brush radius
  vtkNew<vtkIdList> result;
  pointLocator->FindPointsWithinRadius(BrushRadius, polyData->GetPoint(pointId), result);

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
    polyData->Modified();
    // actor->GetMapper()->Update();
    this->Interactor->GetRenderWindow()->Render();
  }
}
