// JavaScript wrapper for vtkMinimalStandardRandomSequence with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkMinimalStandardRandomSequenceEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkMinimalStandardRandomSequence.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkMinimalStandardRandomSequence.h"

template<> void emscripten::internal::raw_destructor<vtkMinimalStandardRandomSequence>(vtkMinimalStandardRandomSequence * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkMinimalStandardRandomSequence_class) {
  emscripten::class_<vtkMinimalStandardRandomSequence, emscripten::base<vtkRandomSequence>>("vtkMinimalStandardRandomSequence")
    .smart_ptr<vtkSmartPointer<vtkMinimalStandardRandomSequence>>("vtkSmartPointer<vtkMinimalStandardRandomSequence>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkMinimalStandardRandomSequence>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkMinimalStandardRandomSequence::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkMinimalStandardRandomSequence& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkMinimalStandardRandomSequence::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkMinimalStandardRandomSequence::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkMinimalStandardRandomSequence::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkMinimalStandardRandomSequence& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("Initialize", &vtkMinimalStandardRandomSequence::Initialize)
    .function("SetSeed", &vtkMinimalStandardRandomSequence::SetSeed)
    .function("SetSeedOnly", &vtkMinimalStandardRandomSequence::SetSeedOnly)
    .function("GetSeed", &vtkMinimalStandardRandomSequence::GetSeed)
    .function("GetValue", &vtkMinimalStandardRandomSequence::GetValue)
    .function("Next", &vtkMinimalStandardRandomSequence::Next)
    .function("GetRangeValue", &vtkMinimalStandardRandomSequence::GetRangeValue)
    .function("GetNextRangeValue", &vtkMinimalStandardRandomSequence::GetNextRangeValue);
}
