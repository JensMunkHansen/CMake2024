#ifndef spsImplicitPolyDataDistanceT_txx
#define spsImplicitPolyDataDistanceT_txx

#include "vtkDataObject.h"
#include "vtkGenericCell.h" // For thread local storage
#include "vtkImplicitFunction.h"
#include "vtkSMPThreadLocalObject.h" // For thread local storage

#include <vtkCellLocator.h>
#include <vtkPolyData.h>

template <typename T, bool HasCellData, bool HasNormals>
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

  //  T ClosestPointAndNorm(T x[3], T awnorm[3], T closestPoint[3]);

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

  T SharedEvaluate(T x[3], T g[3], T closestPoint[3])
  {
    // Set defaults
    T ret = this->NoValue;

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

    T transformedPoint[3] = { x[0], x[1], x[2] };

    // Apply the transform provided by vtkImplicitFunction
    if (this->Transform)
    {
      this->Transform->InternalTransformPoint(x, transformedPoint); // Transform input point
    }

    T p[3];
    vtkIdType cellId;
    int subId;
    T vlen2;

    vtkDataArray* cnorms = nullptr;

    if constexpr (HasCellData && HasNormals)
    {
      // Cast to either vtkFloatArray or vtkDoubleArray
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

      T dist2, weights[3], pcoords[3], awnorm[3] = { 0, 0, 0 };
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
        T transformedGradient[3];

        this->Transform->TransformNormalAtPoint(closestPoint, g, transformedGradient);
        for (int i = 0; i < 3; i++)
        {
          g[i] = transformedGradient[i];
        }
      }
    }

    return ret;
  }

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

#include <vtkArrayDispatch.h>
#include <vtkDataArray.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

struct RandomAccessWorker
{
  vtkIdType Index;

  RandomAccessWorker(vtkIdType idx)
    : Index(idx)
  {
  }

  template <typename ArrayType>
  void operator()(ArrayType* array)
  {
    // ArrayType will be vtkFloatArray, vtkDoubleArray, etc.
    using ValueType = typename ArrayType::ValueType;

    // Perform random access on the array
    ValueType value = array->GetValue(Index);
    std::cout << "Value at index " << Index << ": " << value << std::endl;
  }
};

void ProcessArray(vtkDataArray* array, vtkIdType index)
{
  // Create a dispatcher and use it for random access
  RandomAccessWorker worker(index);
  vtkArrayDispatch::DispatchByValueType<vtkArrayDispatch::AllTypes>::Execute(array, worker);
}
// Example function using direct pointer access
void ProcessRaycastWithKnownArrayType(vtkDataArray* dataArray, vtkIdType index)
{
  vtkFloatArray* floatArray = vtkFloatArray::SafeDownCast(dataArray);
  if (floatArray)
  {
    // Access data pointer directly
    float* dataPtr = static_cast<float*>(floatArray->GetVoidPointer(0));
    // Perform random access
    float value = dataPtr[index];
    std::cout << "Value at index " << index << ": " << value << std::endl;
  }
}
