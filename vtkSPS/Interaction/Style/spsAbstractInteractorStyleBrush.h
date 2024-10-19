#ifndef SPS_ABSTRACT_INTERACTOR_STYLE_BRUSH_H
#define SPS_ABSTRACT_INTERACTOR_STYLE_BRUSH_H

#include <memory>
#include <spsInteractionStyleModule.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkAbstractPointLocator;
class vtkAbstractPicker;
class vtkTransform;

/**
 * @class   spsAbstractInteractorStyleBrush
 * @brief   Abstract class for tools using a brush.
 *
 * This class can be used as a base class for drawing on meshes,
 * sculpting and other operations, which can be applied using a brush.
 */
class SPSINTERACTIONSTYLE_EXPORT spsAbstractInteractorStyleBrush
  : public vtkInteractorStyleTrackballCamera
{
public:
  vtkTypeMacro(spsAbstractInteractorStyleBrush, vtkInteractorStyleTrackballCamera);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  virtual void OnLeftButtonDown() override;
  virtual void OnLeftButtonUp() override;
  virtual void OnMouseMove() override;

  ///@{
  /**
   * Specify the radius of the brush.
   *
   */
  vtkSetMacro(BrushRadius, double);
  vtkGetMacro(BrushRadius, double);
  ///@}

  ///@{
  /**
   * Specify resolution, i.e. how many brush applications for a
   * displacment equal to the @BrushRadius.
   *
   */
  vtkGetMacro(Resolution, int);
  vtkSetMacro(Resolution, int);
  ///@}

  /**
   * Possible values for the locator mode:
   * - OcreePointLocator: Fastest locator to build, but lookups are slow.
   *
   * - PointLocator: Fast locator to build, lookups are fast but could
   *   be faster.
   *
   * - StaticPointLocator: Slowest locator to build, but lookups are
   *   very fasts. Use this for polydata that do not change.
   */
  enum LocatorModeType : int
  {
    OctreePointLocator = 0,
    PointLocator = 1,
    StaticPointLocator = 2
  };

  ///@{
  /**
   * Locator used (default: PointLocator).
   */
  virtual void SetLocatorMode(int LocatorMode);
  vtkGetMacro(LocatorMode, int);
  ///@}

  const char* GetLocatorModeAsString();

protected:
  spsAbstractInteractorStyleBrush();
  ~spsAbstractInteractorStyleBrush() override;
  double BrushRadius;
  int Resolution;
  int LocatorMode = spsAbstractInteractorStyleBrush::PointLocator;

  // TODO: Make this interchangeable
  vtkSmartPointer<vtkAbstractPicker> Picker;

  vtkSmartPointer<vtkAbstractPointLocator> GetLocator(vtkActor* actor, vtkPolyData* polyData);

  void UpdateActorToLocalTransform();

  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData) = 0;

  // Internals
  vtkNew<vtkTransform> ActorToLocalTransform;
  bool IsActive;
  vtkActor* CurrentActor;
  double CurrentLocalPosition[3];
  double LastLocalPosition[3];

private:
  spsAbstractInteractorStyleBrush(const spsAbstractInteractorStyleBrush&) = delete;
  void operator=(const spsAbstractInteractorStyleBrush&) = delete;
  struct vtkInternals;
  std::unique_ptr<vtkInternals> Internals;
};

#endif
