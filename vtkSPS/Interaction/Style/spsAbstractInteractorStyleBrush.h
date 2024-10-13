#ifndef SPS_ABSTRACT_INTERACTOR_STYLE_BRUSH_H
#define SPS_ABSTRACT_INTERACTOR_STYLE_BRUSH_H

#include <spsInteractionStyleModule.h>
#include <unordered_map>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkAbstractPointLocator;
class vtkPointPicker;

class SPSINTERACTIONSTYLE_EXPORT spsAbstractInteractorStyleBrush
  : public vtkInteractorStyleTrackballCamera
{
public:
  vtkTypeMacro(spsAbstractInteractorStyleBrush, vtkInteractorStyleTrackballCamera);
  void PrintSelf(ostream& os, vtkIndent indent) override;
  virtual void OnLeftButtonDown() override;
  virtual void OnLeftButtonUp() override;
  virtual void OnMouseMove() override;
  vtkSetMacro(BrushRadius, double);
  vtkGetMacro(BrushRadius, double);
  vtkGetMacro(Resolution, int);
  vtkSetMacro(Resolution, int);
  vtkGetMacro(UseStaticLocators, bool);
  virtual void SetUseStaticLocators(bool polyDataStatic);

protected:
  using LocatorMapType =
    std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkAbstractPointLocator>>;

  spsAbstractInteractorStyleBrush();
  ~spsAbstractInteractorStyleBrush() override;
  double BrushRadius;
  int Resolution;
  bool UseStaticLocators;
  vtkNew<vtkPointPicker> Picker;

  LocatorMapType LocatorMap;
  vtkSmartPointer<vtkAbstractPointLocator> GetLocator(vtkActor* actor, vtkPolyData* polyData);

  void TransformToLocalCoordinates(
    vtkActor* actor, const double worldPosition[3], double localPosition[3]);

  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData) = 0;

  // Internals
  bool IsActive;
  vtkActor* CurrentActor;
  vtkIdType CurrentPointId;
  double CurrentLocalPosition[3];
  double LastLocalPosition[3]; // Last position where brush was applied

private:
  spsAbstractInteractorStyleBrush(const spsAbstractInteractorStyleBrush&) = delete;
  void operator=(const spsAbstractInteractorStyleBrush&) = delete;
};

#endif
