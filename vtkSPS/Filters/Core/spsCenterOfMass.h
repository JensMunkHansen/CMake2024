/**
 * @class   spsCenterOfMass
 * @brief   Find the center of mass of a set of points.
 *
 * spsCenterOfMass finds the "center of mass" of a vtkPointSet (vtkPolyData
 * or vtkUnstructuredGrid). Optionally, the user can specify to use the scalars
 * as weights in the computation. If this option, UseScalarsAsWeights, is off,
 * each point contributes equally in the calculation.
 *
 * You must ensure Update() has been called before GetCenter will produce a valid
 * value.
 */

#ifndef spsCenterOfMass_h
#define spsCenterOfMass_h

#include "spsABINamespace.h"
#include "spsFiltersCoreModule.h" // For export macro
#include "vtkPointSetAlgorithm.h"

// Question: Why do we need this. Do we have a destructor?
#include "vtkSmartPointer.h"
#include "vtkTransform.h"

SPS_ABI_NAMESPACE_BEGIN
class vtkPoints;
class vtkDataArray;
class vtkTransform;

class SPSFILTERSCORE_EXPORT VTK_MARSHALAUTO spsCenterOfMass : public vtkPointSetAlgorithm
{
public:
  spsCenterOfMass(spsCenterOfMass&&) = delete;
  spsCenterOfMass& operator=(spsCenterOfMass&&) = delete;
  static spsCenterOfMass* New();
  vtkTypeMacro(spsCenterOfMass, vtkPointSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Get the output of the center of mass computation.
   */
  vtkSetVector3Macro(Center, double);
  vtkGetVector3Macro(Center, double);
  ///@}

  ///@{
  /**
   * Get the output of the enclosing radius
   */
  vtkSetMacro(EnclosingRadius, double);
  vtkGetMacro(EnclosingRadius, double);
  ///@}

  ///@{
  /**
   * Set a flag to determine if the points are weighted.
   */
  vtkSetMacro(UseScalarsAsWeights, bool);
  vtkGetMacro(UseScalarsAsWeights, bool);
  ///@}

  ///@{
  /**
   * Set a flag to compute enclosing radius.
   */
  vtkSetMacro(IncludeEnclosingRadius, bool);
  vtkGetMacro(IncludeEnclosingRadius, bool);
  ///@}

  /**
   * This function is called by RequestData. It exists so that
   * other classes may use this computation without constructing
   * a spsCenterOfMass object.  The scalars can be set to nullptr
   * if all points are to be weighted equally.  If scalars are
   * used, it is the caller's responsibility to ensure that the
   * number of scalars matches the number of points, and that
   * the sum of the scalars is a positive value.
   */
  static void ComputeCenterOfMass(vtkPoints* input, vtkDataArray* scalars, double center[3]);

  /**
   * If set, this transform is applied to the center of mass computed.
   */
  vtkSetSmartPointerMacro(Transform, vtkTransform);
  vtkGetSmartPointerMacro(Transform, vtkTransform);

protected:
  vtkSmartPointer<vtkTransform> Transform;
  spsCenterOfMass();

  double ComputeEnclosingRadius(vtkPoints* points, double center[3]);

  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

private:
  spsCenterOfMass(const spsCenterOfMass&) = delete;
  void operator=(const spsCenterOfMass&) = delete;

  bool UseScalarsAsWeights;
  bool IncludeEnclosingRadius;
  double Center[3];
  double EnclosingRadius;
};

SPS_ABI_NAMESPACE_END
#endif
