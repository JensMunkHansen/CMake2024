#include <spsPolyDataPieceFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkInformation.h>
#include <vtkNew.h>
#include <vtkSphereSource.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkTestUtilities.h>
#include <vtkTesting.h>

namespace
{
//------------------------------------------------------------------------------
void TestExpectedOutput(spsPolyDataPieceFilter* pieceFilter, const vtkIdType& nPieces,
  vtkIdType& numberOfPoints, vtkIdType& numberOfCells, const double tolerance = 1e-6)
{
  vtkInformation* outInfo = pieceFilter->GetExecutive()->GetOutputInformation(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES(), nPieces);

  vtkNew<vtkAppendPolyData> appendFilter;

  for (int iPiece = 0; iPiece < nPieces; iPiece++)
  {
    outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER(), iPiece);
    int upstreamPieceNumber =
      pieceFilter->GetInputAlgorithm(0, 0)->GetOutputPortInformation(0)->Get(
        vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER());
    std::cout << "UPDATE_PIECE_NUMBER(spsPolyDataPieceFilter): " << iPiece << std::endl;
    std::cout << "UPDATE_PIECE_NUMBER(vtkSphereSource): " << upstreamPieceNumber << std::endl;
    pieceFilter->Update();
    vtkNew<vtkPolyData> polyData;
    polyData->DeepCopy(pieceFilter->GetOutput());
    appendFilter->AddInputData(polyData);
  }
  vtkNew<vtkCleanPolyData> cleanFilter;
  cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
  // We allow some tolerance
  cleanFilter->SetTolerance(1e-6);

  vtkPolyDataAlgorithm* polyDataAlgorithm = nullptr;
  // Uncomment for skipping cleaning of polydata
  // polyDataAlgorithm = vtkPolyDataAlgorithm::SafeDownCast(appendFilter);
  polyDataAlgorithm = vtkPolyDataAlgorithm::SafeDownCast(cleanFilter);
  polyDataAlgorithm->Update();
  numberOfPoints = polyDataAlgorithm->GetOutput()->GetNumberOfPoints();
  numberOfCells = polyDataAlgorithm->GetOutput()->GetNumberOfCells();
  std::cout << "Number of points: " << numberOfPoints << std::endl;
  std::cout << "Number of cells: " << numberOfCells << std::endl;
}
}

//------------------------------------------------------------------------------
int TestPolyDataPieceFilter(int argc, char* argv[])
{
  vtkIdType nPieces = 4;
  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->SetThetaResolution(8);
  sphereSource->SetPhiResolution(8);
  sphereSource->Update();

  vtkNew<spsPolyDataPieceFilter> pieceFilter;

  vtkIdType nExpectedPoints = sphereSource->GetOutput()->GetNumberOfPoints();
  vtkIdType nExpectedCells = sphereSource->GetOutput()->GetNumberOfCells();
  vtkIdType nPoints = 0;
  vtkIdType nCells = 0;

  int retval = EXIT_SUCCESS;

  // Test trivial producer - we handle subdivision, so no tolerance
  pieceFilter->SetInputData(sphereSource->GetOutput());
  pieceFilter->UpdateInformation();
  TestExpectedOutput(pieceFilter, nPieces, nPoints, nCells, 0.0);
  retval |= !((nExpectedCells == nCells) && (nExpectedPoints == nPoints));

  // Test streaming producer capable of handling piece request
  pieceFilter->SetInputConnection(sphereSource->GetOutputPort());
  pieceFilter->UpdateInformation();
  TestExpectedOutput(pieceFilter, nPieces, nPoints, nCells);
  retval |= !((nExpectedCells == nCells) && (nExpectedPoints == nPoints));

  return retval;
}
