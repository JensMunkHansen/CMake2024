// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkImplicitPolyDataDistance
 * @brief   Implicit function that computes the distance from a point x to the nearest point p on an
 * input vtkPolyData.
 *
 * Implicit function that computes the distance from a point x to the
 * nearest point p on an input vtkPolyData. The sign of the function
 * is set to the sign of the dot product between the angle-weighted
 * pseudonormal at the nearest surface point and the vector x - p.
 * Points interior to the geometry have a negative distance, points on
 * the exterior have a positive distance, and points on the input
 * vtkPolyData have a distance of zero. The gradient of the function
 * is the angle-weighted pseudonormal at the nearest point.
 *
 * Baerentzen, J. A. and Aanaes, H. (2005). Signed distance
 * computation using the angle weighted pseudonormal. IEEE
 * Transactions on Visualization and Computer Graphics, 11:243-253.
 *
 * This code was contributed in the VTK Journal paper:
 * "Boolean Operations on Surfaces in VTK Without External Libraries"
 * by Cory Quammen, Chris Weigle C., Russ Taylor
 * http://hdl.handle.net/10380/3262
 * http://www.midasjournal.org/browse/publication/797
 */

#ifndef spsImplicitPolyDataDistance_h
#define spsImplicitPolyDataDistance_h

#include "spsABINamespace.h"
#include "spsFiltersCoreModule.h" // For export macro
#include "vtkGenericCell.h"       // For thread local storage
#include "vtkImplicitFunction.h"
#include "vtkSMPThreadLocalObject.h" // For thread local storage

SPS_ABI_NAMESPACE_BEGIN
class vtkAbstractCellLocator;
class vtkLocator;
class vtkPolyData;

class SPSFILTERSCORE_EXPORT spsImplicitPolyDataDistance : public vtkImplicitFunction
{
public:
  static spsImplicitPolyDataDistance* New();
  vtkTypeMacro(spsImplicitPolyDataDistance, vtkImplicitFunction);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Return the MTime also considering the Input dependency.
   */
  vtkMTimeType GetMTime() override;

  /**
   * Evaluate plane equation of nearest triangle to point x[3].
   */
  using vtkImplicitFunction::EvaluateFunction;
  double EvaluateFunction(double x[3]) override;

  /**
   * Evaluate function gradient of nearest triangle to point x[3].
   */
  void EvaluateGradient(double x[3], double g[3]) override;

  /**
   * Evaluate plane equation of nearest triangle to point x[3] and provides closest point on an
   * input vtkPolyData.
   */
  double EvaluateFunctionAndGetClosestPoint(double x[3], double closestPoint[3]);

  /**
   * Set the input vtkPolyData used for the implicit function
   * evaluation.  Passes input through an internal instance of
   * vtkTriangleFilter to remove vertices and lines, leaving only
   * triangular polygons for evaluation as implicit planes.
   */
  void SetInput(vtkPolyData* input);

  ///@{
  /**
   * Set/get the function value to use if no input vtkPolyData
   * specified.
   */
  vtkSetMacro(NoValue, double);
  vtkGetMacro(NoValue, double);
  ///@}

  ///@{
  /**
   * Set/get the function gradient to use if no input vtkPolyData
   * specified.
   */
  vtkSetVector3Macro(NoGradient, double);
  vtkGetVector3Macro(NoGradient, double);
  ///@}

  ///@{
  /**
   * Set/get the closest point to use if no input vtkPolyData
   * specified.
   */
  vtkSetVector3Macro(NoClosestPoint, double);
  vtkGetVector3Macro(NoClosestPoint, double);
  ///@}

  ///@{
  /**
   * Set/get the tolerance used for the locator.
   */
  vtkGetMacro(Tolerance, double);
  vtkSetMacro(Tolerance, double);
  ///@}

protected:
  spsImplicitPolyDataDistance();
  ~spsImplicitPolyDataDistance() override;

  /**
   * Create default locator. Used to create one when none is specified.
   */
  void CreateDefaultLocator();

  double SharedEvaluate(double x[3], double g[3], double closestPoint[3]);

  double NoGradient[3];
  double NoClosestPoint[3];
  double NoValue;
  double Tolerance;

  vtkPolyData* Input;
  vtkAbstractCellLocator* Locator;
  vtkSMPThreadLocalObject<vtkGenericCell> TLCell;
  vtkSMPThreadLocalObject<vtkIdList> TLCellIds;

private:
  spsImplicitPolyDataDistance(const spsImplicitPolyDataDistance&) = delete;
  void operator=(const spsImplicitPolyDataDistance&) = delete;
};

SPS_ABI_NAMESPACE_END
#endif
