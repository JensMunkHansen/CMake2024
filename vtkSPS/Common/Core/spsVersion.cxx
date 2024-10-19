/*=========================================================================

  Program:
  Module:    spsVersion.cxx

=========================================================================*/
#include "spsVersion.h"
#include "spsVersionFull.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(spsVersion);

void spsVersion::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

const char* spsVersion::GetVTKVersionFull()
{
  // Since VTK_VERSION_FULL changes with every commit, it is kept out of the
  // header file to avoid excessive rebuilds.
  return VTK_VERSION_FULL;
}

const char* GetVTKVersion()
{
  return VTK_VERSION;
}

const char* spsVersion::GetSpsVersionFull()
{
  // Since VTK_VERSION_FULL changes with every commit, it is kept out of the
  // header file to avoid excessive rebuilds.
  return SPS_VERSION_FULL;
}

const char* GetSpsVersion()
{
  return SPS_VERSION;
}
