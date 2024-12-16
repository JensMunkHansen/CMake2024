// JavaScript wrapper for vtkBuffer with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkBufferEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkBuffer.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkBuffer.h"
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkEmbindUtils.h"

vtkAddDestructor(vtkBuffer<emscripten::val>);
EMSCRIPTEN_BINDINGS(vtkBufferChar_class)
{
  emscripten::class_<vtkBuffer<emscripten::val>, emscripten::base<vtkObject>>("vtkBuffer")
    .smart_ptr<vtkSmartPointer<vtkBuffer<emscripten::val>>>("vtkSmartPointer<vtkBuffer>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkBuffer<emscripten::val>>)
    .class_function("IsTypeOf", emscripten::optional_override([](const std::string &arg_0) -> int {
          return vtkBuffer<emscripten::val>::IsTypeOf(arg_0.c_str());
      }))
    .function("IsA", emscripten::optional_override([](vtkBuffer<emscripten::val> &self, const std::string &arg_0) -> int {
          return self.IsA(arg_0.c_str());
      }))
    .class_function("SafeDownCast", &vtkBuffer<emscripten::val>::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkBuffer<emscripten::val>::NewInstance, emscripten::allow_raw_pointers())
    .function("SetBuffer", &vtkBuffer<emscripten::val>::SetBuffer, emscripten::allow_raw_pointers()); 
}


