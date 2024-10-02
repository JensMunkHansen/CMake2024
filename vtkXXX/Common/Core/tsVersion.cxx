/*=========================================================================

  Program:   
  Module:    tsVersion.cxx

=========================================================================*/
#include "tsVersion.h"
#include "tsVersionFull.h"
#include "vtkObjectFactory.h"

vtkStandardNewMacro(tsVersion);

void tsVersion::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

const char* tsVersion::GetVTKVersionFull()
{
  // Since VTK_VERSION_FULL changes with every commit, it is kept out of the
  // header file to avoid excessive rebuilds.
  return VTK_VERSION_FULL;
}

const char* GetVTKVersion()
{
  return VTK_VERSION;
}

const char* tsVersion::GetTsVersionFull()
{
  // Since VTK_VERSION_FULL changes with every commit, it is kept out of the
  // header file to avoid excessive rebuilds.
  return TS_VERSION;
}

const char* GetTsVersion()
{
  return TS_VERSION;
}
