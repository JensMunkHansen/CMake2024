#ifndef SPS_INTERACTOR_STYLE_DEMO_H
#define SPS_INTERACTOR_STYLE_DEMO_H

#include <spsInteractionStyleModule.h>
#include <unordered_map>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>

class vtkPolyData;
class vtkAbstractPointLocator;
class vtkPointPicker;

class SPSINTERACTIONSTYLE_EXPORT spsInteractorStyleDemo : public vtkInteractorStyleTrackballCamera
{
public:
  static spsInteractorStyleDemo* New();
  vtkTypeMacro(spsInteractorStyleDemo, vtkInteractorStyleTrackballCamera);
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
  spsInteractorStyleDemo();
  ~spsInteractorStyleDemo() = default;
  double BrushRadius;
  int Resolution;
  bool UseStaticLocators;
  vtkNew<vtkPointPicker> Picker;

  std::unordered_map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkAbstractPointLocator>>
    LocatorMap;
  vtkSmartPointer<vtkAbstractPointLocator> GetLocator(vtkActor* actor, vtkPolyData* polyData);

  void TransformToLocalCoordinates(
    vtkActor* actor, const double worldPosition[3], double localPosition[3]);

  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData);

  // Internals
  bool IsActive;
  bool IsFirst;
  vtkActor* CurrentActor;
  vtkIdType CurrentPointId;
  double CurrentPosition[3];
  double CurrentLocalPosition[3];
  double LastLocalPosition[3]; // Last position where brush was applied
  int Counter = 0;

private:
  spsInteractorStyleDemo(const spsInteractorStyleDemo&) = delete;
  void operator=(const spsInteractorStyleDemo&) = delete;
};

#endif
