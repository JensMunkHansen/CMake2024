#include <spsSimpleTriangleSubdivisionFilter.h>
#include <vtkIdList.h>
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>

#include <array>
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
void SubdivideTriangleRecursive(vtkPoints* points, vtkPointData* outputPointData,
  std::vector<Triangle>& triangles, int depth, vtkIdType p0, vtkIdType p1, vtkIdType p2)
{
  if (depth == 0)
  {
    return; // If depth is 0, stop the recursion
  }

  // TODO: Calculate the centroid of the triangle

  // TODO: Insert the centroid point into points array

  // TODO: Interpolate point data for centroid

  // Remove the last triangle (which is being subdivided)
  triangles.pop_back();

  // TODO: and replace it with 3 new triangles and recurse for each triangle
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

  // TODO: Initialize output point data

  // Pre-allocate vector for subdivided triangles
  std::vector<Triangle> subdividedTriangles;
  subdividedTriangles.reserve(estimatedNumTriangles); // Pre-allocate enough space for all triangles

  // Start recursive subdivision
  vtkDebugMacro(<< "Number of triangles (before): " << triangles.size());
  for (const auto& tri : triangles)
  {
    // Push the initial triangle and
    subdividedTriangles.push_back(tri);

    // recursively subdivide it
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
