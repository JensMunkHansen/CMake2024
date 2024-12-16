// JavaScript wrapper for vtkIdTypeArray with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkIdTypeArrayEmbinding.cxx \
 /home/jmh/wasm/vtk/Common/Core/vtkIdTypeArray.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkAbstractArray.h"
#include "vtkIdTypeArray.h"

template<> void emscripten::internal::raw_destructor<vtkIdTypeArray>(vtkIdTypeArray * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkIdTypeArray_class) {
  emscripten::class_<vtkIdTypeArray, emscripten::base<vtkDataArray>>("vtkIdTypeArray")
    .smart_ptr<vtkSmartPointer<vtkIdTypeArray>>("vtkSmartPointer<vtkIdTypeArray>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkIdTypeArray>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdTypeArray::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkIdTypeArray& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkIdTypeArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkIdTypeArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdTypeArray::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkIdTypeArray& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .class_function("ExtendedNew", &vtkIdTypeArray::ExtendedNew, emscripten::allow_raw_pointers())
    .function("GetDataType", &vtkIdTypeArray::GetDataType)
    .function("GetValue", &vtkIdTypeArray::GetValue)
    .function("SetValue", &vtkIdTypeArray::SetValue)
    .function("SetNumberOfValues", &vtkIdTypeArray::SetNumberOfValues)
    .function("InsertValue", &vtkIdTypeArray::InsertValue)
    .function("InsertNextValue", &vtkIdTypeArray::InsertNextValue)
    .function("WritePointer", emscripten::optional_override([](vtkIdTypeArray& self, int arg_0, int arg_1) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.WritePointer( arg_0, arg_1)) / sizeof(int);}))
    .function("GetPointer", emscripten::optional_override([](vtkIdTypeArray& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetPointer( arg_0)) / sizeof(int);}))
    .function("SetArray", emscripten::select_overload<void(vtkIdTypeArray&, std::uintptr_t, int, int)>([](vtkIdTypeArray& self, std::uintptr_t arg_0, int arg_1, int arg_2) -> void { return self.SetArray(reinterpret_cast<int*>(arg_0 * sizeof(int)), arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("SetArray", emscripten::select_overload<void(vtkIdTypeArray&, std::uintptr_t, int, int, int)>([](vtkIdTypeArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void { return self.SetArray(reinterpret_cast<int*>(arg_0 * sizeof(int)), arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .class_function("FastDownCast", &vtkIdTypeArray::FastDownCast, emscripten::allow_raw_pointers())
    .class_function("GetDataTypeValueMin", &vtkIdTypeArray::GetDataTypeValueMin)
    .class_function("GetDataTypeValueMax", &vtkIdTypeArray::GetDataTypeValueMax);
}
