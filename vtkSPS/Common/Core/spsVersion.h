#ifndef spsVersion_h
#define spsVersion_h

#include "spsABINamespace.h"
#include "spsCommonCoreModule.h" // For export macro
#include "spsVersionMacros.h"
#include "vtkObject.h"

#include "vtkVersionFull.h"
#include "vtkVersionMacros.h" // For VTK version

SPS_ABI_NAMESPACE_BEGIN
class SPSCOMMONCORE_EXPORT spsVersion : public vtkObject
{
public:
  static spsVersion* New();
  vtkTypeMacro(spsVersion, vtkObject)
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Return the version of vtk this object is a part of.
   * A variety of methods are included. GetVTKSourceTsVersion returns a string
   * with an identifier which timestamps a particular source tree.
   */
  static const char* GetSpsVersionFull();
  static int GetSpsMajorVersion() { return SPS_MAJOR_VERSION; }
  static int GetSpsMinorVersion() { return SPS_MINOR_VERSION; }
  static int GetSpsBuildVersion() { return SPS_BUILD_VERSION; }
  static const char* GetSpsSourceVersion() { return SPS_SOURCE_VERSION; }

  static const char* GetVTKVersionFull();
  static int GetVTKMajorVersion() { return VTK_MAJOR_VERSION; }
  static int GetVTKMinorVersion() { return VTK_MINOR_VERSION; }
  static int GetVTKBuildVersion() { return VTK_BUILD_VERSION; }
  static const char* GetVTKSourceVersion() { return VTK_SOURCE_VERSION; }

protected:
  spsVersion() = default; // ensure constructor/destructor protected
  ~spsVersion() override = default;

private:
  spsVersion(const spsVersion&) = delete;
  void operator=(const spsVersion&) = delete;
};
SPS_ABI_NAMESPACE_END

extern "C"
{
  SPSCOMMONCORE_EXPORT const char* GetSpsVersion();
}

#endif
