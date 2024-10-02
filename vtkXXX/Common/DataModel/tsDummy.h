#pragma once

#include "spsCommonExecutionModelModule.h" // For export macros
#include "vtkObject.h"

class SPSCOMMONEXECUTIONMODEL_EXPORT vtkDummy : public vtkObject
{
public:
  static vtkDummy* New();
  vtkTypeMacro(vtkDummy, vtkObject)

  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  vtkDummy();
  ~vtkDummy() override;

private:
  vtkDummy(const vtkDummy&) = delete;
  void operator=(const vtkDummy&) = delete;
};
