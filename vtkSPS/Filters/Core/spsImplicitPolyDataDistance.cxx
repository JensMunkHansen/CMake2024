// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#include "spsImplicitPolyDataDistance.h"

#include "vtkCellData.h"
#include "vtkCellLocator.h"
#include "vtkCleanPolyData.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkPolygon.h"
#include "vtkSmartPointer.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkTriangleFilter.h"

VTK_ABI_NAMESPACE_BEGIN
vtkStandardNewMacro(spsImplicitPolyDataDistance);

//------------------------------------------------------------------------------
spsImplicitPolyDataDistance::spsImplicitPolyDataDistance()
{
  this->NoClosestPoint[0] = 0.0;
  this->NoClosestPoint[1] = 0.0;
  this->NoClosestPoint[2] = 0.0;

  this->NoGradient[0] = 0.0;
  this->NoGradient[1] = 0.0;
  this->NoGradient[2] = 1.0;

  this->NoValue = 0.0;

  this->Input = nullptr;
  this->Locator = nullptr;
  this->Tolerance = 1e-12;
}

//------------------------------------------------------------------------------
void spsImplicitPolyDataDistance::SetInput(vtkPolyData* input)
{
  if (this->Input != input)
  {
    // Fix issue #18307: Use vtkCleanPolyData to merge duplicate points in the input PolyData.
    vtkSmartPointer<vtkCleanPolyData> cleanPolyData = vtkSmartPointer<vtkCleanPolyData>::New();
    cleanPolyData->SetInputData(input);
    cleanPolyData->Update();

    // Use a vtkTriangleFilter on the polydata input.
    vtkNew<vtkTriangleFilter> triangleFilter;
    triangleFilter->PassVertsOff();
    triangleFilter->PassLinesOff();

    triangleFilter->SetInputConnection(cleanPolyData->GetOutputPort());
    triangleFilter->Update();

    this->Input = triangleFilter->GetOutput();

    this->Input->BuildLinks();
    this->NoValue = this->Input->GetLength();

    this->CreateDefaultLocator();
    this->Locator->SetDataSet(this->Input);
    this->Locator->SetTolerance(this->Tolerance);
    this->Locator->SetNumberOfCellsPerBucket(10);
    this->Locator->CacheCellBoundsOn();
    this->Locator->AutomaticOn();
    this->Locator->BuildLocator();
  }
}

//------------------------------------------------------------------------------
vtkMTimeType spsImplicitPolyDataDistance::GetMTime()
{
  vtkMTimeType mTime = this->vtkImplicitFunction::GetMTime();
  vtkMTimeType InputMTime;

  if (this->Input != nullptr)
  {
    InputMTime = this->Input->GetMTime();
    mTime = (InputMTime > mTime ? InputMTime : mTime);
  }

  return mTime;
}

//------------------------------------------------------------------------------
spsImplicitPolyDataDistance::~spsImplicitPolyDataDistance()
{
  if (this->Locator)
  {
    this->Locator->UnRegister(this);
    this->Locator = nullptr;
  }
}

//------------------------------------------------------------------------------
void spsImplicitPolyDataDistance::CreateDefaultLocator()
{
  if (this->Locator == nullptr)
  {
    this->Locator = vtkCellLocator::New();
  }
}

//------------------------------------------------------------------------------
double spsImplicitPolyDataDistance::EvaluateFunction(double x[3])
{
  double g[3];
  double p[3];
  return this->SharedEvaluate(
    x, g, p); // get distance value returned, normal and closest point not used
}

//------------------------------------------------------------------------------
double spsImplicitPolyDataDistance::EvaluateFunctionAndGetClosestPoint(
  double x[3], double closestPoint[3])
{
  double g[3];
  return this->SharedEvaluate(x, g, closestPoint); // distance value returned and point on
                                                   // vtkPolyData stored in p (normal not used).
}

//------------------------------------------------------------------------------
void spsImplicitPolyDataDistance::EvaluateGradient(double x[3], double g[3])
{
  double p[3];
  this->SharedEvaluate(
    x, g, p); // get normal, returned distance value not used and closest point not used
}

//------------------------------------------------------------------------------
double spsImplicitPolyDataDistance::SharedEvaluate(double x[3], double g[3], double closestPoint[3])
{
  // Set defaults
  double ret = this->NoValue;

  for (int i = 0; i < 3; i++)
  {
    g[i] = this->NoGradient[i];
  }

  for (int i = 0; i < 3; i++)
  {
    closestPoint[i] = this->NoClosestPoint[i];
  }

  // See if data set with polygons has been specified
  if (this->Input == nullptr || this->Input->GetNumberOfCells() == 0)
  {
    vtkErrorMacro(<< "No polygons to evaluate function!");
    return ret;
  }

  double transformedPoint[3] = { x[0], x[1], x[2] };

  // Apply the transform provided by vtkImplicitFunction
  if (this->Transform)
  {
    this->Transform->InternalTransformPoint(x, transformedPoint); // Transform input point
  }

  double p[3];
  vtkIdType cellId;
  int subId;
  double vlen2;

  vtkDataArray* cnorms = nullptr;
  if (this->Input->GetCellData() && this->Input->GetCellData()->GetNormals())
  {
    cnorms = this->Input->GetCellData()->GetNormals();
  }

  // Get point id of closest point in the dataset
  auto cell = this->TLCell.Local();
  this->Locator->FindClosestPoint(transformedPoint, p, cell, cellId, subId, vlen2);

  if (cellId != -1) // point located
  {
    // dist = | point - transformedPoint |
    ret = std::sqrt(vlen2);
    // grad = (point - transformedPoint) / dist
    for (int i = 0; i < 3; i++)
    {
      g[i] = (p[i] - transformedPoint[i]) / (ret == 0. ? 1. : ret);
    }

    double dist2, weights[3], pcoords[3], awnorm[3] = { 0, 0, 0 };
    cell->EvaluatePosition(p, closestPoint, subId, pcoords, dist2, weights);

    // Face case - weights contains no 0s
    if (weights[0] != 0. && weights[1] != 0. && weights[2] != 0.)
    {
      if (cnorms)
      {
        cnorms->GetTuple(cellId, awnorm);
      }
      else
      {
        vtkPolygon::ComputeNormal(cell->Points, awnorm);
      }
    }
    // Handle other cases as per your original logic
    // ...

    // Sign the distance
    ret *= (vtkMath::Dot(g, awnorm) < 0.) ? 1. : -1.;

    // If a transformation exists, transform the gradient
    if (this->Transform)
    {
      double transformedGradient[3];

      this->Transform->TransformNormalAtPoint(closestPoint, g, transformedGradient);
      for (int i = 0; i < 3; i++)
      {
        g[i] = transformedGradient[i];
      }
    }
  }

  return ret;
}

//------------------------------------------------------------------------------
void spsImplicitPolyDataDistance::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkImplicitFunction::PrintSelf(os, indent);

  os << indent << "NoValue: " << this->NoValue << "\n";
  os << indent << "NoGradient: (" << this->NoGradient[0] << ", " << this->NoGradient[1] << ", "
     << this->NoGradient[2] << ")\n";
  os << indent << "Tolerance: " << this->Tolerance << "\n";

  if (this->Input)
  {
    os << indent << "Input : " << this->Input << "\n";
  }
  else
  {
    os << indent << "Input : (none)\n";
  }
}
VTK_ABI_NAMESPACE_END
