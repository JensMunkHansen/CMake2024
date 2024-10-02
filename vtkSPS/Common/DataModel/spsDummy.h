#pragma once

#include "spsCommonDataModelModule.h" // For export macros
#include "vtkObject.h"

class SPSCOMMONDATAMODEL_EXPORT spsDummy : public vtkObject
{
public:
  static spsDummy* New();
  vtkTypeMacro(spsDummy, vtkObject)

  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  spsDummy();
  ~spsDummy() override;

private:
  spsDummy(const spsDummy&) = delete;
  void operator=(const spsDummy&) = delete;
};
