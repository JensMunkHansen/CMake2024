#include <spsInteractorStylePaintBrush.h>
#include <vtkCamera.h>
#include <vtkCellData.h>
#include <vtkColor.h>
#include <vtkImageData.h>
#include <vtkInformation.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRandomPool.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkTestUtilities.h>
#include <vtkTesting.h>
#include <vtkUnsignedCharArray.h>

#if 0
static char TestInteractorStylePaintBrushLog[] = "# StreamVersion 1.2\n"
                                                 "ExposeEvent 0 299 0 0 0 0 0\n"
                                                 "RenderEvent 0 299 0 0 0 0 0\n"
                                                 "RenderEvent 0 299 0 0 0 0 0\n"
                                                 "EnterEvent 172 8 0 0 0 0 0\n";
#endif

int TestInteractorStylePainBrush(int argc, char* argv[])
{

  vtkNew<vtkSphereSource> sphereSource;
  sphereSource->SetThetaResolution(50);
  sphereSource->SetPhiResolution(50);
  sphereSource->Update();

  // Renderer and window setup
  vtkNew<vtkRenderer> renderer;
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetWindowName("TestInteractorStylePaintBrush");
  renderWindow->AddRenderer(renderer);
  vtkNew<vtkActor> actor;
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  actor->SetMapper(mapper);
  renderer->AddActor(actor);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow);
  vtkNew<spsInteractorStylePaintBrush> style;
  style->SetBrushRadius(0.2);
  interactor->SetInteractorStyle(style);

  // Start rendering
  interactor->Initialize();

  renderer->ResetCamera();
  renderWindow->Render();

  return vtkTesting::InteractorEventLoop(argc, argv, interactor);
}
