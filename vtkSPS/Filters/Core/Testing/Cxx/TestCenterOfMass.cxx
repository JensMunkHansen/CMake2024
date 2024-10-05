#include <spsCenterOfMass.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPointSource.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSMPTools.h>
#include <vtkSmartPointer.h>
#include <vtkTimerLog.h>

#include <cmath>
#include <limits>

template <class A>
bool fuzzyCompare1D(A a, A b)
{
  return std::abs(a - b) < std::numeric_limits<A>::epsilon();
}

template <class A>
bool fuzzyCompare3D(A a[3], A b[3])
{
  return fuzzyCompare1D(a[0], b[0]) && fuzzyCompare1D(a[1], b[1]) && fuzzyCompare1D(a[2], b[2]);
}

int TestCenterOfMass(int, char*[])
{
  // Create a point set of a square
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);
  points->InsertNextPoint(0, 1, 0);
  points->InsertNextPoint(1, 1, 0);

  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Compute the center of mass
  vtkSmartPointer<spsCenterOfMass> centerOfMassFilter = vtkSmartPointer<spsCenterOfMass>::New();
  centerOfMassFilter->SetInputData(polydata);

  // Test unweighted
  {
    centerOfMassFilter->SetUseScalarsAsWeights(false);
    centerOfMassFilter->Update();

    double center[3];
    centerOfMassFilter->GetCenter(center);

    double correct[3] = { 0.5, 0.5, 0 };
    if (!fuzzyCompare3D(center, correct))
    {
      std::cerr << "Error: center is " << center[0] << " " << center[1] << " " << center[2]
                << " but should be " << correct[0] << " " << correct[1] << " " << center[2]
                << std::endl;
      return EXIT_FAILURE;
    }
  }

  // Test weighted
  {
    centerOfMassFilter->SetUseScalarsAsWeights(true);

    vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
    weights->SetNumberOfValues(4);
    weights->SetValue(0, 1);
    weights->SetValue(1, 1);
    weights->SetValue(2, 1);
    weights->SetValue(3, 2);

    polydata->GetPointData()->SetScalars(weights);

    centerOfMassFilter->Update();

    double center[3];
    centerOfMassFilter->GetCenter(center);

    double correct[3] = { 0.6, 0.6, 0 };
    if (!fuzzyCompare3D(center, correct))
    {
      std::cerr << "Error: center is " << center[0] << " " << center[1] << " " << center[2]
                << " but should be " << correct[0] << " " << correct[1] << " " << center[2]
                << std::endl;
      return EXIT_FAILURE;
    }
  }
#if 1
  vtkNew<vtkTimerLog> tl;
  vtkNew<vtkPointSource> pointSource;
  centerOfMassFilter->SetUseScalarsAsWeights(false);

  vtkIdType step = 100000;
  vtkSMPTools::SetBackend("Sequential");
  for (vtkIdType i = 1; i < 10; i++)
  {
    pointSource->SetNumberOfPoints(i * step);
    pointSource->Update();
    centerOfMassFilter->SetInputConnection(pointSource->GetOutputPort());
    tl->StartTimer();
    centerOfMassFilter->Update();
    tl->StopTimer();
    std::cout << "Sequential: " << tl->GetElapsedTime() << std::endl;
  }

  vtkSMPTools::SetBackend("TBB");
  // vtkSMPTools::SetBackend("STDThread");
  for (vtkIdType i = 1; i < 10; i++)
  {
    pointSource->SetNumberOfPoints(i * step);
    pointSource->Update();
    centerOfMassFilter->SetInputConnection(pointSource->GetOutputPort());
    tl->StartTimer();
    centerOfMassFilter->Update();
    tl->StopTimer();
    std::cout << "Threaded: " << tl->GetElapsedTime() << std::endl;
  }
#endif
  return EXIT_SUCCESS;
}
