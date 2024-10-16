#ifndef SPS_INTERACTOR_STYLE_BRUSH_H
#define SPS_INTERACTOR_STYLE_BRUSH_H

#include <spsInteractionStyleModule.h>
#include <unordered_map>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkAbstractPointLocator;
class vtkPointPicker;

class SPSINTERACTIONSTYLE_EXPORT spsInteractorStyleBrush : public vtkInteractorStyleTrackballCamera
{
public:
  static spsInteractorStyleBrush* New();
  vtkTypeMacro(spsInteractorStyleBrush, vtkInteractorStyleTrackballCamera);

  virtual void OnLeftButtonDown() override;
  virtual void OnLeftButtonUp() override;
  virtual void OnMouseMove() override;
  vtkSetMacro(BrushRadius, double);
  vtkGetMacro(BrushRadius, double);
  vtkGetMacro(UseStaticLocators, bool);
  virtual void SetUseStaticLocators(bool polyDataStatic);
  // Set picker
protected:
  spsInteractorStyleBrush();
  ~spsInteractorStyleBrush() = default;
  double BrushRadius;
  bool UseStaticLocators;
  bool IsActive;
  vtkActor* CurrentActor;
  vtkIdType CurrentPointId;
  double CurrentPosition[3];
  double CurrentLocalPosition[3];
  double LastLocalPosition[3]; // Last position where brush was applied

  vtkNew<vtkPointPicker> Picker;
  std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkAbstractPointLocator>>
    LocatorMap;
  vtkSmartPointer<vtkAbstractPointLocator> GetLocator(vtkActor* actor, vtkPolyData* polyData);

  void TransformToLocalCoordinates(
    vtkActor* actor, const double worldPosition[3], double localPosition[3]);

  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData);

private:
  spsInteractorStyleBrush(const spsInteractorStyleBrush&) = delete;
  void operator=(const spsInteractorStyleBrush&) = delete;
};

#endif
