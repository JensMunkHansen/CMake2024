#pragma once

#include <spsInteractionStyleModule.h>
#include <unordered_map>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkPointLocator;
class vtkStaticPointLocator;
class vtkPointPicker;

class SPSINTERACTIONSTYLE_EXPORT spsInteractorStylePaintBrush
  : public vtkInteractorStyleTrackballCamera
{
public:
  static spsInteractorStylePaintBrush* New();
  vtkTypeMacro(spsInteractorStylePaintBrush, vtkInteractorStyleTrackballCamera);

  virtual void OnLeftButtonDown() override;
  virtual void OnLeftButtonUp() override;
  virtual void OnMouseMove() override;
  vtkSetMacro(BrushRadius, double);
  vtkGetMacro(BrushRadius, double);

protected:
  spsInteractorStylePaintBrush();
  ~spsInteractorStylePaintBrush() = default;
  double BrushRadius;
  bool IsActive;
  std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkStaticPointLocator>> LocatorMap;

  vtkNew<vtkPointPicker> Picker;

  bool ActorHasColors(vtkActor* actor);

  void AddInitialColor(vtkActor* actor, vtkPolyData* polyData);
  void ApplyBrush(vtkActor* actor, vtkPolyData* polyData, vtkIdType pointId);

private:
  spsInteractorStylePaintBrush(const spsInteractorStylePaintBrush&) = delete;
  void operator=(const spsInteractorStylePaintBrush&) = delete;
};
