// JavaScript wrapper for vtkRandomSequence with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkRandomSequenceEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkRandomSequence.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkRandomSequence.h"

template<> void emscripten::internal::raw_destructor<vtkRandomSequence>(vtkRandomSequence * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkRandomSequence_class) {
  emscripten::class_<vtkRandomSequence, emscripten::base<vtkObject>>("vtkRandomSequence")
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkRandomSequence::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkRandomSequence& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkRandomSequence::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkRandomSequence::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkRandomSequence::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkRandomSequence& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("GetNextValue", &vtkRandomSequence::GetNextValue);
}
