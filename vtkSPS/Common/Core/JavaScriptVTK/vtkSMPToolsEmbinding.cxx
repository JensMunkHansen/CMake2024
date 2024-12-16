// JavaScript wrapper for vtkSMPTools with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkSMPToolsEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkSMPTools.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkSMPTools.h"


EMSCRIPTEN_BINDINGS(vtkSMPTools_class) {
  emscripten::class_<vtkSMPTools>("vtkSMPTools")
    .class_function("GetBackend", emscripten::optional_override([]() -> std::string {  return vtkSMPTools::GetBackend();}))
    .class_function("SetBackend", emscripten::optional_override([]( const std::string & arg_0) -> bool {  return vtkSMPTools::SetBackend( arg_0.c_str());}))
    .class_function("Initialize", &vtkSMPTools::Initialize)
    .class_function("GetEstimatedNumberOfThreads", &vtkSMPTools::GetEstimatedNumberOfThreads)
    .class_function("GetEstimatedDefaultNumberOfThreads", &vtkSMPTools::GetEstimatedDefaultNumberOfThreads)
    .class_function("SetNestedParallelism", &vtkSMPTools::SetNestedParallelism)
    .class_function("GetNestedParallelism", &vtkSMPTools::GetNestedParallelism)
    .class_function("IsParallelScope", &vtkSMPTools::IsParallelScope)
    .class_function("GetSingleThread", &vtkSMPTools::GetSingleThread);
}
