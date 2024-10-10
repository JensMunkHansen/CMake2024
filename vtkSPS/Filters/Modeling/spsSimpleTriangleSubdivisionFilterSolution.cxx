#include <spsSimpleTriangleSubdivisionFilter.h>
#include <vtkCellArray.h>
#include <vtkDataArrayAccessor.h>
#include <vtkDataArrayRange.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkIdList.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <array>
#include <vector>

namespace
{
using Triangle = std::array<vtkIdType, 3>;

void InitializeOutputPointData(vtkPointData* inputPointData, vtkPointData* outputPointData,
  vtkIdType numInputPoints, vtkIdType estimatedNumPoints)
{
  // Loop through each array in inputPointData
  for (int i = 0; i < inputPointData->GetNumberOfArrays(); ++i)
  {
    vtkDataArray* inputArray = inputPointData->GetArray(i);
    if (inputArray)
    {
      // Create a matching array in the output point data
      vtkSmartPointer<vtkDataArray> outputArray =
        vtkSmartPointer<vtkDataArray>::Take(inputArray->NewInstance());
      outputArray->SetName(inputArray->GetName());
      outputArray->SetNumberOfComponents(inputArray->GetNumberOfComponents());
      outputArray->SetNumberOfTuples(
        estimatedNumPoints); // Pre-allocate for all points (existing + new)

      // Copy the data from input to output for the existing points
      for (vtkIdType j = 0; j < numInputPoints; ++j)
      {
        outputArray->SetTuple(j, inputArray->GetTuple(j));
      }

      // Add the output array to the output point data
      outputPointData->AddArray(outputArray);
    }
  }
}

//------------------------------------------------------------------------------
void EstimateSubdivisionSize(vtkIdType numInputPoints, vtkIdType numInputTriangles,
  vtkIdType& estimatedNumPoints, vtkIdType& estimatedNumTriangles, int subdivisions)
{
  // Estimate the number of triangles after subdivision.
  estimatedNumTriangles = numInputTriangles * static_cast<vtkIdType>(std::pow(3, subdivisions));

  // Estimate the number of points after subdivision.
  // Formula: P + T * (3^d - 1) / 2 (adding new points at each level)
  estimatedNumPoints = numInputPoints + numInputTriangles * (std::pow(3, subdivisions) - 1) / 2;
}

//------------------------------------------------------------------------------
bool ConvertCellArrayToTriangles(vtkCellArray* cells, std::vector<Triangle>& triangleList)
{
  vtkIdType npts;
  const vtkIdType* pts;

  cells->InitTraversal();
  while (cells->GetNextCell(npts, pts))
  {
    if (npts != 3)
    {
      return false;
    }
    triangleList.push_back({ pts[0], pts[1], pts[2] });
  }
  return true;
}

//------------------------------------------------------------------------------
template <typename T>
void SubdivideTriangleRecursive(vtkDataArray* dataArray, vtkPointData* outputPointData,
  std::vector<Triangle>& triangles, int depth, vtkIdType p0, vtkIdType p1, vtkIdType p2)
{
  if (depth == 0)
  {
    return;
  }

  // Use DataArrayTupleRange for efficient access.
  auto range = vtk::DataArrayTupleRange<3>(dataArray);

  // Access the coordinates of p0, p1, and p2.
  const auto& p0Coords = range[p0];
  const auto& p1Coords = range[p1];
  const auto& p2Coords = range[p2];

  // Compute the centroid of the triangle.
  T centroid[3];
  for (int i = 0; i < 3; ++i)
  {
    centroid[i] = (p0Coords[i] + p1Coords[i] + p2Coords[i]) / static_cast<T>(3.0);
  }

  // Insert the centroid into the points array.
  vtkIdType centroidId = dataArray->InsertNextTuple(centroid);

  // Interpolate the point data for the new centroid.
  vtkNew<vtkIdList> pointIds;
  pointIds->InsertNextId(p0);
  pointIds->InsertNextId(p1);
  pointIds->InsertNextId(p2);
  double weights[3] = { 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0 }; // Equal weights.
  outputPointData->InterpolatePoint(outputPointData, centroidId, pointIds, weights);

  // Replace the current triangle with three smaller triangles.
  triangles.pop_back();

  triangles.push_back({ p0, centroidId, p1 });
  SubdivideTriangleRecursive<T>(
    dataArray, outputPointData, triangles, depth - 1, p0, centroidId, p1);

  triangles.push_back({ p1, p2, centroidId });
  SubdivideTriangleRecursive<T>(
    dataArray, outputPointData, triangles, depth - 1, p1, p2, centroidId);

  triangles.push_back({ p2, p0, centroidId });
  SubdivideTriangleRecursive<T>(
    dataArray, outputPointData, triangles, depth - 1, p2, p0, centroidId);
}

//------------------------------------------------------------------------------
template <typename T>
int ExecuteSubdivision(vtkPolyData* input, vtkPolyData* output, int subdivisions)
{
  std::vector<Triangle> triangles;
  if (!ConvertCellArrayToTriangles(input->GetPolys(), triangles))
  {
    vtkErrorWithObjectMacro(
      input, "Non-triangle cell found. Input mesh must contain only triangles.");
    return 0;
  }

  vtkSmartPointer<vtkPoints> newPoints = vtkSmartPointer<vtkPoints>::New();
  newPoints->SetDataType(vtkTypeTraits<T>::VTKTypeID());

  vtkNew<vtkCellArray> newPolys;

  vtkIdType numInputPoints = input->GetNumberOfPoints();
  vtkIdType numInputTriangles = input->GetNumberOfCells();
  vtkIdType estimatedNumPoints = 0;
  vtkIdType estimatedNumTriangles = 0;

  EstimateSubdivisionSize(
    numInputPoints, numInputTriangles, estimatedNumPoints, estimatedNumTriangles, subdivisions);

  newPoints->SetNumberOfPoints(estimatedNumPoints);
  newPolys->EstimateSize(estimatedNumTriangles, 3);

  newPoints->DeepCopy(input->GetPoints());
  vtkDataArray* dataArray = newPoints->GetData();

  vtkPointData* inputPointData = input->GetPointData();
  vtkPointData* outputPointData = output->GetPointData();
  //  outputPointData->InterpolateAllocate(inputPointData, estimatedNumPoints);

  InitializeOutputPointData(inputPointData, outputPointData, numInputPoints, estimatedNumPoints);

  std::vector<Triangle> subdividedTriangles;
  subdividedTriangles.reserve(estimatedNumTriangles);

  for (const auto& tri : triangles)
  {
    subdividedTriangles.push_back(tri);
    SubdivideTriangleRecursive<T>(
      dataArray, outputPointData, subdividedTriangles, subdivisions, tri[0], tri[1], tri[2]);
  }

  for (const auto& tri : subdividedTriangles)
  {
    newPolys->InsertNextCell(3, tri.data());
  }

  output->SetPoints(newPoints);
  output->SetPolys(newPolys);

  return 1;
}
}

//------------------------------------------------------------------------------
spsSimpleTriangleSubdivisionFilter::spsSimpleTriangleSubdivisionFilter() = default;
spsSimpleTriangleSubdivisionFilter::~spsSimpleTriangleSubdivisionFilter() = default;
vtkStandardNewMacro(spsSimpleTriangleSubdivisionFilter);

//------------------------------------------------------------------------------
int spsSimpleTriangleSubdivisionFilter::RequestData(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  vtkPolyData* input = vtkPolyData::GetData(inputVector[0]);
  vtkPolyData* output = vtkPolyData::GetData(outputVector);

  if (!input || !input->GetPolys())
  {
    vtkErrorMacro("Invalid input: No triangles found.");
    return 0;
  }

  int dataType = input->GetPoints()->GetDataType();
  if (dataType == VTK_FLOAT)
  {
    return ExecuteSubdivision<float>(input, output, NumberOfSubdivisions);
  }
  else if (dataType == VTK_DOUBLE)
  {
    return ExecuteSubdivision<double>(input, output, NumberOfSubdivisions);
  }
  else
  {
    vtkErrorMacro("Unsupported point data type.");
    return 0;
  }
}
