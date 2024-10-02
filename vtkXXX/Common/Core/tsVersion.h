#ifndef tsVersion_h
#define tsVersion_h

#include "tsCommonCoreModule.h" // For export macro
#include "tsVersionMacros.h"
#include "vtkObject.h"

#include "vtkVersionFull.h"
#include "vtkVersionMacros.h" // For VTK version

class TSCOMMONCORE_EXPORT tsVersion : public vtkObject
{
public:
  static tsVersion* New();
  vtkTypeMacro(tsVersion, vtkObject)
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Return the version of vtk this object is a part of.
   * A variety of methods are included. GetVTKSourceTsVersion returns a string
   * with an identifier which timestamps a particular source tree.
   */
  static const char* GetTsVersionFull();
  static int GetTsMajorVersion() { return TS_MAJOR_VERSION; }
  static int GetTsMinorVersion() { return TS_MINOR_VERSION; }
  static int GetTsBuildVersion() { return TS_BUILD_VERSION; }
  static const char* GetTsSourceVersion() { return TS_SOURCE_VERSION; }

  static const char* GetVTKVersionFull();
  static int GetVTKMajorVersion() { return VTK_MAJOR_VERSION; }
  static int GetVTKMinorVersion() { return VTK_MINOR_VERSION; }
  static int GetVTKBuildVersion() { return VTK_BUILD_VERSION; }
  static const char* GetVTKSourceVersion() { return VTK_SOURCE_VERSION; }

protected:
  tsVersion() = default; // ensure constructor/destructor protected
  ~tsVersion() override = default;

private:
  tsVersion(const tsVersion&) = delete;
  void operator=(const tsVersion&) = delete;
};

extern "C"
{
  TSCOMMONCORE_EXPORT const char* GetTsVersion();
}

extern "C"
{
  TSCOMMONCORE_EXPORT const char* GetVTKVersion();
}

#endif
