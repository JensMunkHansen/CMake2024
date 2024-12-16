// JavaScript wrapper for vtkUnsignedCharArray with embind
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args
\
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkUnsignedCharArrayEmbinding.cxx
\ /home/jmh/github/vtk/Common/Core/vtkUnsignedCharArray.h
*/
#include "vtkAbstractArray.h"
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkIndent.h"
#include "vtkObjectBase.h"
#include "vtkUnsignedCharArray.h"
#include "vtkVariant.h"
#include <emscripten.h>
#include <string>

template <>
void emscripten::internal::raw_destructor<vtkUnsignedCharArray>(vtkUnsignedCharArray* ptr)
{
  ptr->Delete();
}
EMSCRIPTEN_BINDINGS(vtkUnsignedCharArray_class)
{
  emscripten::class_<vtkUnsignedCharArray, emscripten::base<vtkDataArray>>("vtkUnsignedCharArray")
    .smart_ptr<vtkSmartPointer<vtkUnsignedCharArray>>("vtkSmartPointer<vtkUnsignedCharArray>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkUnsignedCharArray>)
    .class_function("IsTypeOf",
      emscripten::optional_override([](const std::string& arg_0) -> int
        { return vtkUnsignedCharArray::IsTypeOf(arg_0.c_str()); }))
    .function("IsA",
      emscripten::optional_override([](vtkUnsignedCharArray& self, const std::string& arg_0) -> int
        { return self.IsA(arg_0.c_str()); }))
    .class_function(
      "SafeDownCast", &vtkUnsignedCharArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkUnsignedCharArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType",
      emscripten::optional_override([](const std::string& arg_0) -> int
        { return vtkUnsignedCharArray::GetNumberOfGenerationsFromBaseType(arg_0.c_str()); }))
    .function("GetNumberOfGenerationsFromBase",
      emscripten::optional_override([](vtkUnsignedCharArray& self, const std::string& arg_0) -> int
        { return self.GetNumberOfGenerationsFromBase(arg_0.c_str()); }))
    .class_function(
      "ExtendedNew", &vtkUnsignedCharArray::ExtendedNew, emscripten::allow_raw_pointers())
    .function("GetDataType", &vtkUnsignedCharArray::GetDataType)
    .function("GetValue", &vtkUnsignedCharArray::GetValue)
    .function("SetValue", &vtkUnsignedCharArray::SetValue)
    .function("SetNumberOfValues", &vtkUnsignedCharArray::SetNumberOfValues)
    .function("InsertValue", &vtkUnsignedCharArray::InsertValue)
    .function("InsertNextValue", &vtkUnsignedCharArray::InsertNextValue)
    .function("WritePointer",
      emscripten::optional_override(
        [](vtkUnsignedCharArray& self, int arg_0, int arg_1) -> std::uintptr_t
        {
          return reinterpret_cast<std::uintptr_t>(self.WritePointer(arg_0, arg_1)) /
            sizeof(unsigned char);
        }))
    .function("GetPointer",
      emscripten::optional_override(
        [](vtkUnsignedCharArray& self, int arg_0) -> std::uintptr_t {
          return reinterpret_cast<std::uintptr_t>(self.GetPointer(arg_0)) / sizeof(unsigned char);
        }))
    .function("SetArray",
      emscripten::select_overload<void(vtkUnsignedCharArray&, std::uintptr_t, int, int)>(
        [](vtkUnsignedCharArray& self, std::uintptr_t arg_0, int arg_1, int arg_2) -> void
        {
          return self.SetArray(
            reinterpret_cast<unsigned char*>(arg_0 * sizeof(unsigned char)), arg_1, arg_2);
        }),
      emscripten::allow_raw_pointers())
    .function("SetArray",
      emscripten::select_overload<void(vtkUnsignedCharArray&, std::uintptr_t, int, int, int)>(
        [](
          vtkUnsignedCharArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void
        {
          return self.SetArray(
            reinterpret_cast<unsigned char*>(arg_0 * sizeof(unsigned char)), arg_1, arg_2, arg_3);
        }),
      emscripten::allow_raw_pointers())
    .class_function(
      "FastDownCast", &vtkUnsignedCharArray::FastDownCast, emscripten::allow_raw_pointers())
    .class_function("GetDataTypeValueMin", &vtkUnsignedCharArray::GetDataTypeValueMin)
    .class_function("GetDataTypeValueMax", &vtkUnsignedCharArray::GetDataTypeValueMax);
}
