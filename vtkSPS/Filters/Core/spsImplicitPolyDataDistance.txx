#ifndef spsImplicitPolyDataDistanceT_txx
#define spsImplicitPolyDataDistanceT_txx

#include "vtkDataObject.h"
#include "vtkGenericCell.h" // For thread local storage
#include "vtkImplicitFunction.h"
#include "vtkSMPThreadLocalObject.h" // For thread local storage

#include <vtkCellLocator.h>
#include <vtkPolyData.h>

template <typename T>
class spsImplicitPolyDataDistanceT
{
public:
  /**
   * Evaluate plane equation of nearest triangle to point x[3].
   */
  using vtkImplicitFunction::EvaluateFunction;
  T EvaluateFunction(T x[3]);

  /**
   * Evaluate function gradient of nearest triangle to point x[3].
   */
  void EvaluateGradient(T x[3], T g[3]);

  /**
   * Evaluate plane equation of nearest triangle to point x[3] and provides closest point on an
   * input vtkPolyData.
   */
  T EvaluateFunctionAndGetClosestPoint(T x[3], T closestPoint[3]);

  /**
   * Evaluate plane equation of nearest triangle to point x[3] and provides closest point on an
   * input vtkPolyData as well as the graident.
   */
  T EvaluateFunctionGradientAndGetClosestPoint(T x[3], T g[3], T closestPoint[3]);

  T ClosestPointAndNorm(T x[3], T awnorm[3], T closestPoint[3]);

  /**
   * Set the input vtkPolyData used for the implicit function
   * evaluation.  Passes input through an internal instance of
   * vtkTriangleFilter to remove vertices and lines, leaving only
   * triangular polygons for evaluation as implicit planes.
   */
  void SetInput(vtkPolyData* input);
  vtkGetObjectMacro(Input, vtkPolyData);

  ///@{
  /**
   * Set/get the function gradient to use if no input vtkPolyData
   * specified.
   */
  void SetNoGradient(T noGradient[3]);
  T* GetNoGradient();
  ///@}

  ///@{
  /**
   * Set/get the closest point to use if no input vtkPolyData
   * specified.
   */
  void SetNoClosestPoint(T noClosestPoint[3]);
  T* GetNoClosestPoint();
  ///@}

  ///@{
  /**
   * Set/get the tolerance used for the locator.
   */
  void SetTolerance(T tolerance);
  T GetTolerance();
  ///@}

protected:
  spsImplicitPolyDataDistanceT();
  ~spsImplicitPolyDataDistanceT();

  T SharedEvaluate(T x[3], T g[3], T closestPoint[3]);

  /**
   * Create default locator. Used to create one when none is specified.
   */
  void CreateDefaultLocator();

  T NoGradient[3];
  T NoClosestPoint[3];
  T NoValue;
  T Tolerance;

  vtkPolyData* Input;
  vtkCellLocator* Locator;
  vtkSMPThreadLocalObject<vtkGenericCell> TLCell;
  vtkSMPThreadLocalObject<vtkIdList> TLCellIds;

private:
  spsImplicitPolyDataDistanceT(const spsImplicitPolyDataDistanceT&) = delete;
  void operator=(const spsImplicitPolyDataDistanceT&) = delete;
};

#endif
