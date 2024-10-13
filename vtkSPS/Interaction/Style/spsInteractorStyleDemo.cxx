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
  this->Counter = 0;
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::PrintSelf(ostream& os, vtkIndent indent)
{
  os << indent << "Counter: " << this->Counter << "\n";
  Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::OnLeftButtonDown()
{
  this->Counter = 0;
  Superclass::OnLeftButtonDown();
}

//------------------------------------------------------------------------------
void spsInteractorStyleDemo::ApplyBrush(vtkActor* actor, vtkPolyData* polyData)
{
  vtkDebugMacro("" << __FUNCTION__);
  this->Counter++;
  if (!ActorHasColors(actor))
  {
    AddInitialColor(actor, polyData);
  }

  vtkSmartPointer<vtkAbstractPointLocator> pointLocator = this->GetLocator(actor, polyData);

  // Find points within the brush radius
  vtkNew<vtkIdList> result;

  if (this->IsActive)
  {
    pointLocator->FindPointsWithinRadius(BrushRadius, this->LastLocalPosition, result);
  }
  else
  {
    // OnButtonUp(), here IsActive is false
    pointLocator->FindPointsWithinRadius(BrushRadius, this->CurrentLocalPosition, result);
  }
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
