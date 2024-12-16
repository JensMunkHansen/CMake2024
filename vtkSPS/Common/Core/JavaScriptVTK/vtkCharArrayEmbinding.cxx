// JavaScript wrapper for vtkCharArray with embind
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args
\
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCharArrayEmbinding.cxx
\ /home/jmh/github/vtk/Common/Core/vtkCharArray.h
*/
#include "vtkAbstractArray.h"
#include "vtkCharArray.h"
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkIndent.h"
#include "vtkObjectBase.h"
#include "vtkVariant.h"
#include <emscripten.h>
#include <string>

template <>
void emscripten::internal::raw_destructor<vtkCharArray>(vtkCharArray* ptr)
{
  ptr->Delete();
}
EMSCRIPTEN_BINDINGS(vtkCharArray_class)
{
  emscripten::class_<vtkCharArray, emscripten::base<vtkDataArray>>("vtkCharArray")
    .smart_ptr<vtkSmartPointer<vtkCharArray>>("vtkSmartPointer<vtkCharArray>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkCharArray>)
    .class_function("IsTypeOf",
      emscripten::optional_override(
        [](const std::string& arg_0) -> int { return vtkCharArray::IsTypeOf(arg_0.c_str()); }))
    .function("IsA",
      emscripten::optional_override([](vtkCharArray& self, const std::string& arg_0) -> int
        { return self.IsA(arg_0.c_str()); }))
    .class_function("SafeDownCast", &vtkCharArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkCharArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType",
      emscripten::optional_override([](const std::string& arg_0) -> int
        { return vtkCharArray::GetNumberOfGenerationsFromBaseType(arg_0.c_str()); }))
    .function("GetNumberOfGenerationsFromBase",
      emscripten::optional_override([](vtkCharArray& self, const std::string& arg_0) -> int
        { return self.GetNumberOfGenerationsFromBase(arg_0.c_str()); }))
    .class_function("ExtendedNew", &vtkCharArray::ExtendedNew, emscripten::allow_raw_pointers())
    .function("GetDataType", &vtkCharArray::GetDataType)
    //.function("GetValue", &vtkCharArray::GetValue)
    //.function("SetValue", &vtkCharArray::SetValue)
    .function("SetNumberOfValues", &vtkCharArray::SetNumberOfValues)
    .function("InsertValue", &vtkCharArray::InsertValue)
    .function("InsertNextValue", &vtkCharArray::InsertNextValue)
    .function("WritePointer",
      emscripten::optional_override([](vtkCharArray& self, int arg_0, int arg_1) -> std::string
        { return self.WritePointer(arg_0, arg_1); }))
    .function("GetPointer",
      emscripten::optional_override(
        [](vtkCharArray& self, int arg_0) -> std::string { return self.GetPointer(arg_0); }))
    .function("SetArray",
      emscripten::select_overload<void(vtkCharArray&, std::uintptr_t, int, int)>(
        [](vtkCharArray& self, std::uintptr_t arg_0, int arg_1, int arg_2) -> void
        { return self.SetArray(reinterpret_cast<char*>(arg_0 * sizeof(char)), arg_1, arg_2); }))
    .function("SetArray",
      emscripten::select_overload<void(vtkCharArray&, std::uintptr_t, int, int, int)>(
        [](vtkCharArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void {
          return self.SetArray(reinterpret_cast<char*>(arg_0 * sizeof(char)), arg_1, arg_2, arg_3);
        }))
    .class_function("FastDownCast", &vtkCharArray::FastDownCast, emscripten::allow_raw_pointers())
    .class_function("GetDataTypeValueMin", &vtkCharArray::GetDataTypeValueMin)
    .class_function("GetDataTypeValueMax", &vtkCharArray::GetDataTypeValueMax);
}
