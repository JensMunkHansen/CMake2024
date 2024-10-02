#include "spsDummy.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(spsDummy);

spsDummy::spsDummy() {}
spsDummy::~spsDummy() {}

void spsDummy::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
