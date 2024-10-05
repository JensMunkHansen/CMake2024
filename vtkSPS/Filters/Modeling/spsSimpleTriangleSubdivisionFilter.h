#include "vtkCellArray.h"
#include "vtkCellArrayIterator.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkIdList.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkPolyDataAlgorithm.h"
#include "vtkSmartPointer.h"
#include <array>
#include <cmath>
#include <vector>

class spsSimpleTriangleSubdivisionFilter : public vtkPolyDataAlgorithm
{
public:
  static spsSimpleTriangleSubdivisionFilter* New();
  vtkTypeMacro(spsSimpleTriangleSubdivisionFilter, vtkPolyDataAlgorithm);

  // Set the number of subdivisions
  vtkSetMacro(NumberOfSubdivisions, int);
  vtkGetMacro(NumberOfSubdivisions, int);

protected:
  spsSimpleTriangleSubdivisionFilter();
  ~spsSimpleTriangleSubdivisionFilter() override;

  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

private:
  int NumberOfSubdivisions = 1;

  using Triangle = std::array<vtkIdType, 3>;

  // Function to subdivide a triangle recursively
  void SubdivideTriangleRecursive(vtkPoints* points, vtkPointData* outputPointData,
    std::vector<Triangle>& triangles, int depth, vtkIdType p0, vtkIdType p1, vtkIdType p2);

  // Function to convert the vtkCellArray to std::vector<std::array<vtkIdType, 3>>
  bool ConvertCellArrayToTriangles(vtkCellArray* cells, std::vector<Triangle>& triangleList);

  // Helper function to estimate number of points and triangles
  void EstimateSubdivisionSize(vtkIdType numInputPoints, vtkIdType numInputTriangles,
    vtkIdType& estimatedNumPoints, vtkIdType& estimatedNumTriangles, int subdivisions);

  void PreAllocateOutputPointData(
    vtkPointData* inputPointData, vtkPointData* outputPointData, vtkIdType estimatedNumPoints);

  void InitializeOutputPointData(vtkPointData* inputPointData, vtkPointData* outputPointData,
    vtkIdType numInputPoints, vtkIdType estimatedNumPoints);

  void InitializeOutputPointData(
    vtkPointData* inputPointData, vtkPointData* outputPointData, vtkIdType estimatedNumPoints);
};
