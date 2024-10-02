#include "vtkDummy.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkDummy);

vtkDummy::vtkDummy() {}
vtkDummy::~vtkDummy() {}

void vtkDummy::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
