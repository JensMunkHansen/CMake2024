#ifndef SPS_INTERACTOR_STYLE_DEMO_H
#define SPS_INTERACTOR_STYLE_DEMO_H

#include <spsAbstractInteractorStyleBrush.h>
#include <spsInteractionStyleModule.h>

class vtkPolyData;

class SPSINTERACTIONSTYLE_EXPORT spsInteractorStyleDemo : public spsAbstractInteractorStyleBrush
{
public:
  static spsInteractorStyleDemo* New();
  vtkTypeMacro(spsInteractorStyleDemo, spsAbstractInteractorStyleBrush);
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  spsInteractorStyleDemo();
  ~spsInteractorStyleDemo() = default;
  virtual void OnLeftButtonDown() override;
  virtual void ApplyBrush(vtkActor* actor, vtkPolyData* polyData) override;

  int Counter = 0;

private:
  spsInteractorStyleDemo(const spsInteractorStyleDemo&) = delete;
  void operator=(const spsInteractorStyleDemo&) = delete;
};

#endif
