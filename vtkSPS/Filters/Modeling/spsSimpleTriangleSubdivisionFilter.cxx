#include <spsSimpleTriangleSubdivisionFilter.h>
#include <vtkCellArray.h>
#include <vtkCellArrayIterator.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkIdList.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkSmartPointer.h>

#include <array>
#include <cmath>
#include <vector>

namespace
{
using Triangle = std::array<vtkIdType, 3>;

//------------------------------------------------------------------------------
void EstimateSubdivisionSize(vtkIdType numInputPoints, vtkIdType numInputTriangles,
  vtkIdType& estimatedNumPoints, vtkIdType& estimatedNumTriangles, int subdivisions)
{
  // Estimate the number of triangles after subdivision
  estimatedNumTriangles = numInputTriangles * static_cast<vtkIdType>(std::pow(3, subdivisions));

  // Estimate the number of points after subdivision
  // Formula: P + T * (3^d - 1) / 2 (adding new points at each level)
  estimatedNumPoints = numInputPoints + numInputTriangles * (std::pow(3, subdivisions) - 1) / 2;
}

//------------------------------------------------------------------------------
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
void SubdivideTriangleRecursive(vtkPoints* points, vtkPointData* outputPointData,
  std::vector<Triangle>& triangles, int depth, vtkIdType p0, vtkIdType p1, vtkIdType p2)
{
  if (depth == 0)
  {
    return; // If depth is 0, stop the recursion
  }

  // Calculate the centroid of the triangle
  double p0Coords[3], p1Coords[3], p2Coords[3], centroid[3];
  points->GetPoint(p0, p0Coords);
  points->GetPoint(p1, p1Coords);
  points->GetPoint(p2, p2Coords);

  for (int i = 0; i < 3; ++i)
  {
    centroid[i] = (p0Coords[i] + p1Coords[i] + p2Coords[i]) / 3.0;
  }

  // Insert the centroid point into points array
  vtkIdType centroidId = points->InsertNextPoint(centroid);

  // Interpolate point data for centroid
  vtkNew<vtkIdList> pointIds;
  pointIds->InsertNextId(p0);
  pointIds->InsertNextId(p1);
  pointIds->InsertNextId(p2);
  double weights[3] = { 1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0 }; // Equal weighting for interpolation
  outputPointData->InterpolatePoint(outputPointData, centroidId, pointIds, weights);

  // Remove the last triangle (which is being subdivided) and replace it with 3 new triangles
  triangles.pop_back();

  // Subdivide the triangle into 3 smaller triangles
  triangles.push_back({ p0, centroidId, p1 });
  SubdivideTriangleRecursive(points, outputPointData, triangles, depth - 1, p0, centroidId, p1);

  triangles.push_back({ p1, p2, centroidId });
  SubdivideTriangleRecursive(points, outputPointData, triangles, depth - 1, p1, p2, centroidId);

  triangles.push_back({ p2, p0, centroidId });
  SubdivideTriangleRecursive(points, outputPointData, triangles, depth - 1, p2, p0, centroidId);
}
}

//------------------------------------------------------------------------------
spsSimpleTriangleSubdivisionFilter::spsSimpleTriangleSubdivisionFilter() = default;

//------------------------------------------------------------------------------
spsSimpleTriangleSubdivisionFilter::~spsSimpleTriangleSubdivisionFilter() = default;

// VTK macro to enable object creation
vtkStandardNewMacro(spsSimpleTriangleSubdivisionFilter);

//------------------------------------------------------------------------------
int spsSimpleTriangleSubdivisionFilter::RequestData(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
  // Get the input and output polydata
  vtkPolyData* input = vtkPolyData::GetData(inputVector[0]);
  vtkPolyData* output = vtkPolyData::GetData(outputVector);

  // Ensure input contains triangles only
  if (!input || !input->GetPolys())
  {
    vtkErrorMacro("Invalid input: No triangles found.");
    return 0;
  }

  // Convert the cell array into a vector of triangles
  std::vector<Triangle> triangles;
  if (!ConvertCellArrayToTriangles(input->GetPolys(), triangles))
  {
    vtkErrorMacro("Non-triangle cell found. Input mesh must contain only triangles.");
    return 0; // Error if non-triangle cells are found
  }

  // Create new points and polys for the output
  vtkNew<vtkPoints> newPoints;
  vtkNew<vtkCellArray> newPolys;

  // Pre-allocate memory for points and cells
  vtkIdType numInputPoints = input->GetNumberOfPoints();
  vtkIdType numInputTriangles = input->GetNumberOfCells();
  vtkIdType estimatedNumPoints = 0;
  vtkIdType estimatedNumTriangles = 0;

  EstimateSubdivisionSize(numInputPoints, numInputTriangles, estimatedNumPoints,
    estimatedNumTriangles, NumberOfSubdivisions);

  newPoints->SetNumberOfPoints(estimatedNumPoints);
  newPolys->EstimateSize(estimatedNumTriangles, 3);

  // Copy input points to the new points array
  newPoints->DeepCopy(input->GetPoints());

  // Set up point data copying (interpolated in recursion)
  vtkPointData* inputPointData = input->GetPointData();
  vtkPointData* outputPointData = output->GetPointData();

  // outputPointData->InterpolateAllocate(inputPointData, estimatedNumPoints);

  InitializeOutputPointData(inputPointData, outputPointData, numInputPoints, estimatedNumPoints);

  // Pre-allocate vector for subdivided triangles
  std::vector<Triangle> subdividedTriangles;
  subdividedTriangles.reserve(estimatedNumTriangles); // Pre-allocate enough space for all triangles

  // Start recursive subdivision
  vtkDebugMacro(<< "Number of triangles (before): " << triangles.size());
  for (const auto& tri : triangles)
  {
    // Push the initial triangle and recursively subdivide it
    subdividedTriangles.push_back(tri);
    SubdivideTriangleRecursive(newPoints, outputPointData, subdividedTriangles,
      NumberOfSubdivisions, tri[0], tri[1], tri[2]);
  }

  vtkDebugMacro(<< "Number of triangles (after): " << subdividedTriangles.size());
  // Insert subdivided triangles into newPolys
  for (const auto& tri : subdividedTriangles)
  {
    newPolys->InsertNextCell(3, tri.data());
  }

  vtkDebugMacro(<< "Output array: " << output->GetPointData()->GetArray(0)->GetNumberOfTuples());
  // Set the output polydata points and cells
  output->SetPoints(newPoints);
  output->SetPolys(newPolys);

  return 1; // Success
}
