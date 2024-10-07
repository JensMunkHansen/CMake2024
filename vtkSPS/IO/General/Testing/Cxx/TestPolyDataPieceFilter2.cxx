#include <spsPolyDataPieceFilter.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkColor.h>
#include <vtkImageData.h>
#include <vtkInformation.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRandomPool.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkTestUtilities.h>
#include <vtkTesting.h>
#include <vtkUnsignedCharArray.h>

static char TestPolyDataPieceFilter2Log[] = "# StreamVersion 1.2\n"
                                            "ExposeEvent 0 299 0 0 0 0 0\n"
                                            "RenderEvent 0 299 0 0 0 0 0\n"
                                            "RenderEvent 0 299 0 0 0 0 0\n"
                                            "EnterEvent 172 8 0 0 0 0 0\n";

namespace
{
void ColorCells(vtkPolyData* polyData, double color[3])
{
  vtkNew<vtkUnsignedCharArray> cellColors;
  cellColors->SetNumberOfComponents(3);
  cellColors->SetNumberOfTuples(polyData->GetNumberOfCells());
  vtkNew<vtkRandomPool> pool;
  pool->PopulateDataArray(cellColors, 0, 255);
  polyData->GetCellData()->SetScalars(cellColors);
}
}

int TestPolyDataPieceFilter2(int argc, char* argv[])
{

  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->SetThetaResolution(30);
  sphereSource->SetPhiResolution(30);
  sphereSource->Update();

  vtkNew<spsPolyDataPieceFilter> pieceFilter;
  pieceFilter->SetInputConnection(sphereSource->GetOutputPort());
  // pieceFilter->SetInputData(sphereSource->GetOutput());

  // Renderer and window setup
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetWindowName("TestPolyDataPieceFilter2");
  renderWindow->AddRenderer(renderer);
  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow);

  pieceFilter->UpdateInformation();

  // Set up the number of pieces(streaming)
  vtkIdType nPieces = 16;
  vtkInformation* outInfo = pieceFilter->GetExecutive()->GetOutputInformation(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES(), nPieces);

  for (vtkIdType iPiece = 0; iPiece < nPieces; iPiece++)
  {

    outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER(), iPiece);
    pieceFilter->Update();
    std::cout << "UPDATE_PIECE_NUMBER(spsPolyDataPieceFilter): " << iPiece << std::endl;
    vtkIdType iUpstreamPiece = sphereSource->GetOutputInformation(0)->Get(
      vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER());
    std::cout << "UPDATE_PIECE_NUMBER(vtkSphereSource): " << iUpstreamPiece << std::endl;
    vtkNew<vtkPolyData> polyData;
    polyData->DeepCopy(pieceFilter->GetOutput());
    // Debug
    std::cout << "#cells: " << polyData->GetNumberOfCells() << std::endl;
    std::cout << "#points: " << polyData->GetNumberOfPoints() << std::endl;
    // Color the mesh
    // vtk_color_all_cells(polyData)
    // Display
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);
    mapper->SetScalarModeToUseCellData();
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
  }

  // Start rendering
  interactor->Initialize();

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(0.5);
  renderWindow->Render();

  return vtkTesting::InteractorEventLoop(argc, argv, interactor, TestPolyDataPieceFilter2Log);
}
