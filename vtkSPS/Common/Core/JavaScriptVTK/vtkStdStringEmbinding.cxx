// JavaScript wrapper for vtkStdString with embind
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args
\
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkStdStringEmbinding.cxx
\ /home/jmh/github/vtk/Common/Core/vtkStdString.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkStdString.h"
#include "vtkVariant.h"
#include <emscripten.h>
#include <string>

namespace
{
// Factory functions to create vtkStdString objects
vtkStdString* create_vtkStdString_from_char(const char* s)
{
  return new vtkStdString(s);
}

vtkStdString* create_vtkStdString_from_string(const std::string& s)
{
  return new vtkStdString(s);
}
}

EMSCRIPTEN_BINDINGS(vtkStdString_class)
{
  emscripten::class_<vtkStdString>("vtkStdString")
    .constructor<>()
    //    .function("c_str", &vtkStdString::c_str, emscripten::allow_raw_pointers())
    .class_function("fromChar", &create_vtkStdString_from_char, emscripten::allow_raw_pointers())
    .class_function(
      "fromString", &create_vtkStdString_from_string, emscripten::allow_raw_pointers());

  // Bind const char* type
  //  emscripten::register_vector<std::string::value_type>("vector<string::value_type>");
}
