#pragma once

#include <spsInteractionStyleModule.h>
#include <unordered_map>
#include <vtkInteractorStyleMultiTouchCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkStaticPointLocator;
class vtkPointPicker;

class SPSINTERACTIONSTYLE_EXPORT spsInteractorStyleTouchPaintBrush
  : public vtkInteractorStyleMultiTouchCamera
{
public:
  static spsInteractorStyleTouchPaintBrush* New();
  vtkTypeMacro(spsInteractorStyleTouchPaintBrush, vtkInteractorStyleMultiTouchCamera);

  virtual void OnLeftButtonDown() override;
  virtual void OnLeftButtonUp() override;
  virtual void OnMouseMove() override;
  vtkSetMacro(BrushRadius, double);
  vtkGetMacro(BrushRadius, double);

protected:
  spsInteractorStyleTouchPaintBrush();
  ~spsInteractorStyleTouchPaintBrush() = default;
  double BrushRadius;
  bool IsActive;
  std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkStaticPointLocator>> LocatorMap;

  vtkNew<vtkPointPicker> Picker;

  bool ActorHasColors(vtkActor* actor);

  void AddInitialColor(vtkActor* actor, vtkPolyData* polyData);
  void ApplyBrush(vtkActor* actor, vtkPolyData* polyData, vtkIdType pointId);

private:
  spsInteractorStyleTouchPaintBrush(const spsInteractorStyleTouchPaintBrush&) = delete;
  void operator=(const spsInteractorStyleTouchPaintBrush&) = delete;
};
