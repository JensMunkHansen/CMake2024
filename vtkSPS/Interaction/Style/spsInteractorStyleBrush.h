#pragma once

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

protected:
  spsInteractorStyleBrush();
  ~spsInteractorStyleBrush() = default;
  double BrushRadius;
  bool UseStaticLocators;
  bool IsActive;
  vtkIdType CurrentPointId;
  vtkNew<vtkPointPicker> Picker;
  std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkAbstractPointLocator>>
    LocatorMap;
  vtkSmartPointer<vtkAbstractPointLocator> GetLocator(vtkActor* actor, vtkPolyData* polyData);

  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData, vtkIdType pointId);

private:
  spsInteractorStyleBrush(const spsInteractorStyleBrush&) = delete;
  void operator=(const spsInteractorStyleBrush&) = delete;
};
