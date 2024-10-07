#include <spsSimpleTriangleSubdivisionFilter.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkColor.h>
#include <vtkImageData.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRandomPool.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTestUtilities.h>
#include <vtkTesting.h>
#include <vtkUnsignedCharArray.h>

static char TestSimpleTriangleSubdivisionLog[] = "# StreamVersion 1.2\n"
                                                 "ExposeEvent 0 299 0 0 0 0 0\n"
                                                 "RenderEvent 0 299 0 0 0 0 0\n"
                                                 "RenderEvent 0 299 0 0 0 0 0\n"
                                                 "EnterEvent 172 8 0 0 0 0 0\n";

namespace
{
void ColorPointsRandomly(vtkPolyData* polyData)
{
  vtkNew<vtkUnsignedCharArray> colors;
  colors->SetNumberOfComponents(3);
  colors->SetNumberOfTuples(polyData->GetNumberOfPoints());
  colors->SetName("Colors");
  vtkNew<vtkRandomPool> pool;
  pool->PopulateDataArray(colors, 0, 255);
  polyData->GetPointData()->SetScalars(colors);
  polyData->GetPointData()->SetActiveScalars("Colors");
}
void ColorCellsRandomly(vtkPolyData* polyData)
{
  vtkNew<vtkUnsignedCharArray> cellColors;
  cellColors->SetNumberOfComponents(3);
  cellColors->SetNumberOfTuples(polyData->GetNumberOfCells());
  vtkNew<vtkRandomPool> pool;
  pool->PopulateDataArray(cellColors, 0, 255);
  polyData->GetCellData()->SetScalars(cellColors);
}
}

int TestSimpleTriangleSubdivision(int argc, char* argv[])
{
  vtkNew<vtkSphereSource> sphere;
  sphere->Update();
  vtkPolyData* inPolyData = sphere->GetOutput();

  ColorPointsRandomly(inPolyData);

  vtkIdType nInputPoints = inPolyData->GetNumberOfPoints();
  vtkIdType nInputCells = inPolyData->GetNumberOfCells();

  vtkNew<spsSimpleTriangleSubdivisionFilter> subdivision;
  vtkIdType nSubdivisions = 1;
  subdivision->SetNumberOfSubdivisions(nSubdivisions);

  subdivision->SetInputData(inPolyData);
  subdivision->Update();

  vtkPolyData* outPolyData = subdivision->GetOutput();

  ColorCellsRandomly(outPolyData);

  vtkIdType nOutputPoints = outPolyData->GetNumberOfPoints();
  vtkIdType nOutputCells = outPolyData->GetNumberOfCells();

  int retval = 0;

  // Check that we have the correct number of points and cells
  retval |= !(nOutputCells == nInputCells * static_cast<vtkIdType>(std::pow(3, nSubdivisions)));
  retval |= !(nOutputPoints == nInputPoints + nInputCells * (std::pow(3, nSubdivisions) - 1) / 2);

  std::cout << "nOutputCells: " << nOutputCells << std::endl;
  std::cout << "nOutputPoints: " << nOutputPoints << std::endl;

  if (retval != 0)
  {
    return 1;
  }
  // Visual test (regression)
  // Create the render window, renderer and interactor->
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetWindowName("TestSimpleTriangleSubdivision");
  renderWindow->AddRenderer(renderer);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow);

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(outPolyData);
  mapper->SetScalarModeToUseCellData();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  renderer->AddActor(actor);

  interactor->Initialize();

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(0.5);
  renderWindow->Render();

  return vtkTesting::InteractorEventLoop(argc, argv, interactor, TestSimpleTriangleSubdivisionLog);
}
