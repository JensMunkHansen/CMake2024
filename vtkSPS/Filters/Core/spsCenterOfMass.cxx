#include "spsCenterOfMass.h"
#include "spsMacros.h"

#include "vtkArrayDispatch.h"
#include "vtkArrayDispatch.txx"
#include "vtkDataArray.h"
#include "vtkDataArrayRange.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPointSet.h"
#include "vtkSMPThreadLocal.h"
#include "vtkSMPTools.h"
#include "vtkTransform.h"

#include <array>
#include <cassert>

SPS_ABI_NAMESPACE_BEGIN

namespace
{
template <typename TPoints>
struct CenterFunctor
{
  TPoints* Points;
  std::array<double, 3> Center;
  vtkSMPThreadLocal<std::array<double, 3>> TLCenter;
  CenterFunctor(const CenterFunctor&) = delete;
  CenterFunctor(CenterFunctor&&) = delete;
  CenterFunctor& operator=(const CenterFunctor&) = delete;
  CenterFunctor& operator=(CenterFunctor&&) = delete;
  CenterFunctor(TPoints* points)
    : Points(points)
  {
  }

  void Initialize()
  {
    std::array<double, 3>& tlcenter = this->TLCenter.Local();
    tlcenter.fill(0.0);
  }

  void operator()(vtkIdType begin, vtkIdType end)
  {
    const auto& points = vtk::DataArrayTupleRange<3>(this->Points);
    std::array<double, 3>& center = this->TLCenter.Local();

    for (vtkIdType pointId = begin; pointId < end; ++pointId)
    {
      const auto& point = points[pointId];
      for (vtkIdType i = 0; i < 3; i++)
      {
        center[i] += point[i];
      }
    }
  }

  void Reduce()
  {
    this->Center.fill(0.0);
    std::cout << "TLCenter(size): " << this->TLCenter.size() << std::endl;
    for (auto& center : this->TLCenter)
    {
      for (vtkIdType i = 0; i < 3; i++)
      {
        this->Center[i] += center[i];
      }
    }
    vtkIdType numberOfPoints = this->Points->GetNumberOfTuples();
    for (vtkIdType i = 0; i < 3; i++)
    {
      this->Center[i] /= numberOfPoints;
    }
  }
};

template <typename TPoints, typename TScalars>
struct CenterFunctorWeighted
{
  TPoints* Points;
  TScalars* Scalars;
  std::array<double, 3> Center;
  vtkSMPThreadLocal<std::array<double, 3>> TLCenter;
  vtkSMPThreadLocal<double> TLWeight;

  CenterFunctorWeighted(TPoints* points, TScalars* scalars)
    : Points(points)
    , Scalars(scalars)
  {
    assert("pre: wrong array size" && Scalars->GetNumberOfTuples() == Points->GetNumberOfTuples());
  }

  void Initialize()
  {
    std::array<double, 3>& tlcenter = this->TLCenter.Local();
    tlcenter.fill(0.0);
    this->TLWeight.Local() = 0.0;
  }

  void operator()(vtkIdType begin, vtkIdType end)
  {
    std::array<double, 3>& center = this->TLCenter.Local();
    double& weightTotal = this->TLWeight.Local();

#if 0
    vtkDataArrayAccessor<TPoints> v(this->Points);
    vtkDataArrayAccessor<TScalars> m(this->Scalars);

    for (vtkIdType pointId = begin; pointId < end; ++pointId)
    {
      for (vtkIdType i = 0; i < 3; i++)
      {
        center[i] += m.Get(pointId, 0) * v.Get(pointId, i);
      }
      weightTotal += m.Get(pointId, 0);
    }
#else
    const auto& points = vtk::DataArrayTupleRange<3>(this->Points);
    const auto& scalars = vtk::DataArrayValueRange<1>(this->Scalars);

    for (vtkIdType pointId = begin; pointId < end; ++pointId)
    {
      const auto& point = points[pointId];
      const auto& weight = scalars[pointId];
      for (vtkIdType i = 0; i < 3; i++)
      {
        center[i] += weight * point[i];
      }
      weightTotal += (double)weight;
    }
#endif
  }

  void Reduce()
  {
    this->Center.fill(0.0);
    double weightTotal = 0.0;

    for (auto& center : this->TLCenter)
    {
      for (vtkIdType i = 0; i < 3; i++)
      {
        this->Center[i] += center[i];
      }
    }
    for (auto& weight : this->TLWeight)
    {
      weightTotal += weight;
    }
    assert("pre: sum of weights must be positive" && weightTotal > 0.0);
    if (weightTotal > 0.0)
    {
      for (vtkIdType i = 0; i < 3; i++)
      {
        this->Center[i] /= weightTotal;
      }
    }
  }
};

struct CenterWorker
{
  double Center[3];
  CenterWorker() = default;
  template <typename TPoints>
  void operator()(TPoints* points)
  {
    CenterFunctor<TPoints> functor(points);
    vtkSMPTools::For(0, points->GetNumberOfTuples(), 5e6 /*vtkSMPTools::THRESHOLD*/, functor);
    memcpy(Center, &functor.Center[0], 3 * sizeof(double));
  }
  template <typename TPoints, typename TScalars>
  void operator()(TPoints* points, TScalars* scalars)
  {
    CenterFunctorWeighted<TPoints, TScalars> functor(points, scalars);
    vtkSMPTools::For(0, points->GetNumberOfTuples(), 5e6 /*vtkSMPTools::THRESHOLD*/, functor);
    memcpy(Center, &functor.Center[0], 3 * sizeof(double));
  }
};
}

vtkStandardNewMacro(spsCenterOfMass);

spsCenterOfMass::spsCenterOfMass()
{
  this->UseScalarsAsWeights = false;
  this->IncludeEnclosingRadius = true;
  this->Center[0] = this->Center[1] = this->Center[2] = 0.0;
  this->EnclosingRadius = 0.0;
  this->SetNumberOfOutputPorts(0);
  this->Transform = nullptr;
}

double spsCenterOfMass::ComputeEnclosingRadius(vtkPoints* points, double center[3])
{
  vtkIdType n = points->GetNumberOfPoints();
  double distance2 = 0.0;
  for (vtkIdType i = 0; i < n; i++)
  {
    double point[3];
    points->GetPoint(i, point);
    distance2 = std::max(distance2, vtkMath::Distance2BetweenPoints(center, point));
  }
  return sqrt(distance2);
}

void spsCenterOfMass::ComputeCenterOfMass(
  vtkPoints* points, vtkDataArray* scalars, double center[3])
{
  // Threaded version of computing center-of-mass
  CenterWorker centerWorker;

  // Define our dispatchers.
  typedef vtkArrayDispatch::DispatchByValueType<vtkArrayDispatch::Reals> Dispatcher;
  typedef vtkArrayDispatch::Dispatch2ByValueType<vtkArrayDispatch::Reals,
    vtkArrayDispatch::AllTypes>
    DispatcherUsingScalars;

  if (scalars)
  {
    if (!DispatcherUsingScalars::Execute(points->GetData(), scalars, centerWorker))
    {
      centerWorker(points->GetData(), scalars);
    }
  }
  else
  {
    if (!Dispatcher::Execute(points->GetData(), centerWorker))
    {
      centerWorker(points->GetData());
    }
  }
  memcpy(center, &centerWorker.Center[0], 3 * sizeof(double));
}

int spsCenterOfMass::RequestData(vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector, vtkInformationVector* vtkNotUsed(outputVector))
{
  // Get the input and output
  vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
  vtkPointSet* input = vtkPointSet::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkPoints* points = input->GetPoints();

  if (points == nullptr || points->GetNumberOfPoints() == 0)
  {
    this->Center[0] = this->Center[1] = this->Center[2] = 0.0;
    this->EnclosingRadius = 0.0;
    vtkDebugMacro("Input must have at least 1 point!");
    return 1;
  }

  vtkDataArray* scalars = nullptr;

  if (this->UseScalarsAsWeights)
  {
    scalars = input->GetPointData()->GetScalars();

    if (!scalars)
    {
      vtkErrorWithObjectMacro(input, "To use weights PointData::Scalars must be set!");
      return 1;
    }
  }

  double center[3];
  ComputeCenterOfMass(points, scalars, center);

  if (this->GetTransform() != nullptr)
  {
    this->GetTransform()->InternalTransformPoint(center, center);
  }
  this->SetCenter(center);

  if (this->IncludeEnclosingRadius)
  {
    this->EnclosingRadius = this->ComputeEnclosingRadius(points, this->Center);
  }
  this->CheckAbort();

  return 1;
}

void spsCenterOfMass::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Center: " << this->Center[0] << " " << this->Center[1] << " " << this->Center[2]
     << endl;

  os << indent << "UseScalarsAsWeights: " << this->UseScalarsAsWeights << endl;
  os << indent << "IncludeEnclosingRadius: " << this->IncludeEnclosingRadius << endl;
}
SPS_ABI_NAMESPACE_END
