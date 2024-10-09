#pragma once

#include <spsFiltersModelingModule.h>
#include <vtkPolyDataAlgorithm.h>

class vtkPointData;
class vtkInformationVector;

class SPSFILTERSMODELING_EXPORT spsSimpleTriangleSubdivisionFilter : public vtkPolyDataAlgorithm
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
};
