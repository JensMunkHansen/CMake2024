#include "spsPolyDataPieceFilter.h"
#include "vtkAlgorithmOutput.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkTrivialProducer.h"

#include <map>

vtkStandardNewMacro(spsPolyDataPieceFilter);

//------------------------------------------------------------------------------
spsPolyDataPieceFilter::spsPolyDataPieceFilter()
{
  this->PiecesHandledUpstream = true;
}

//------------------------------------------------------------------------------
spsPolyDataPieceFilter::~spsPolyDataPieceFilter() = default;

//------------------------------------------------------------------------------
void spsPolyDataPieceFilter::PrintSelf(std::ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "PiecesHandledUpstream" << std::endl;
}

//------------------------------------------------------------------------------
int spsPolyDataPieceFilter::RequestInformation(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  vtkDebugMacro(<< __FUNCTION__);
  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkNotUsed(outInfo);
  int canHandlePieceRequest = inInfo->Get(vtkAlgorithm::CAN_HANDLE_PIECE_REQUEST());

  vtkTrivialProducer* trivialProducer = vtkTrivialProducer::SafeDownCast(
    this->GetInputConnection(/* port */ 0, /* index */ 0)->GetProducer());
  if (trivialProducer || !canHandlePieceRequest)
  {
    this->PiecesHandledUpstream = false;
  }
  else
  {
    this->PiecesHandledUpstream = true;
  }
  return 1;
}

//------------------------------------------------------------------------------
int spsPolyDataPieceFilter::RequestUpdateExtent(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  vtkDebugMacro(<< __FUNCTION__);

  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  // Get the piece and number of pieces
  int piece = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER());
  int numPieces = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES());
  int ghostLevel = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_GHOST_LEVELS());

  // Request the correct piece of data from upstream
  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER(), piece);
  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES(), numPieces);
  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_GHOST_LEVELS(), ghostLevel);

  return 1;
}

//------------------------------------------------------------------------------
int spsPolyDataPieceFilter::RequestData(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  vtkDebugMacro(<< __FUNCTION__);

  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  vtkPolyData* input = vtkPolyData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
  vtkPolyData* output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  if (!input || input->GetNumberOfCells() == 0)
  {
    return 0;
  }

  if (this->PiecesHandledUpstream)
  {
    // We act like a pass-through filter
    output->ShallowCopy(input);
    this->CheckAbort();
    return 1;
  }

  // Get the piece number and total number of pieces
  int piece = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_PIECE_NUMBER());
  int numPieces = outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_NUMBER_OF_PIECES());

  // Calculate the range of cells for this piece
  vtkIdType numCells = input->GetNumberOfCells();
  vtkIdType cellsPerPiece = numCells / numPieces;
  vtkIdType startCell = piece * cellsPerPiece;
  vtkIdType endCell = (piece == numPieces - 1) ? numCells : (startCell + cellsPerPiece);

  vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> newPolys = vtkSmartPointer<vtkCellArray>::New();

  vtkSmartPointer<vtkPointData> newPointData = nullptr;
  vtkSmartPointer<vtkCellData> newCellData = nullptr;

  if (input->GetCellData()->GetNumberOfArrays() > 0)
  {
    // Preallocate cell data for the output
    newCellData = vtkSmartPointer<vtkCellData>::New();
    newCellData->InterpolateAllocate(input->GetCellData(), endCell - startCell);
  }

  // Check if the input has point data
  if (input->GetPointData()->GetNumberOfArrays() > 0)
  {
    // Preallocate point data for the output
    newPointData = vtkSmartPointer<vtkPointData>::New();
    newPointData->InterpolateAllocate(input->GetPointData(), endCell - startCell);
  }

  std::map<vtkIdType, vtkIdType> pointMap; // Map from old point ID to new point ID

  // Loop through the cells and extract them for this piece
  for (vtkIdType cellId = startCell; cellId < endCell; ++cellId)
  {
    vtkIdType npts;
    const vtkIdType* pts;
    input->GetCellPoints(cellId, npts, pts);

    vtkSmartPointer<vtkIdList> newCell = vtkSmartPointer<vtkIdList>::New();
    // newCell->SetNumberOfIds(3); /* Only triangles */
    for (vtkIdType i = 0; i < npts; ++i)
    {
      vtkIdType oldPtId = pts[i];

      // If the point hasn't been added yet, add it to the new points list
      if (pointMap.find(oldPtId) == pointMap.end())
      {
        // TODO: Use a pre-allocated array
        vtkIdType newPtId = newPoints->InsertNextPoint(input->GetPoint(oldPtId));

        if (newPointData)
        {
          newPointData->CopyData(input->GetPointData(), oldPtId, newPtId);
        }
        pointMap[oldPtId] = newPtId;
      }

      // Add the point to the new cell
      newCell->InsertNextId(pointMap[oldPtId]);
      // newCell->InsertId(i, pointMap[oldPtId]); /* Only triangles */
    }

    // Insert the new cell
    newPolys->InsertNextCell(newCell); /* TODO: Use a pre-allocated array */

    // Copy cell data only if it exists
    if (newCellData)
    {
      newCellData->CopyData(input->GetCellData(), cellId, cellId - startCell);
    }
  }

  // Finalize the points and cell arrays by signaling that the structures are complete
  newPoints->Squeeze(); // Ensure that no extra memory is being used
  newPolys->Squeeze();  // Finalize the cell array to match the actual size

  // Set the new points and cells to the output
  output->SetPoints(newPoints);
  output->SetPolys(newPolys);

  // Ensure the cell data is updated and finalized
  if (newCellData)
  {
    output->GetCellData()->ShallowCopy(newCellData);
  }
  // Ensure the point data is updated and finalized
  if (newPointData)
  {
    output->GetPointData()->ShallowCopy(newPointData);
  }

  return 1;
}
