// JavaScript wrapper for vtkDoubleArray with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkDoubleArrayEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkDoubleArray.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkAbstractArray.h"
#include "vtkDoubleArray.h"

template<> void emscripten::internal::raw_destructor<vtkDoubleArray>(vtkDoubleArray * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkDoubleArray_class) {
  emscripten::class_<vtkDoubleArray, emscripten::base<vtkDataArray>>("vtkDoubleArray")
    .smart_ptr<vtkSmartPointer<vtkDoubleArray>>("vtkSmartPointer<vtkDoubleArray>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkDoubleArray>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkDoubleArray::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkDoubleArray& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkDoubleArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkDoubleArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkDoubleArray::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkDoubleArray& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .class_function("ExtendedNew", &vtkDoubleArray::ExtendedNew, emscripten::allow_raw_pointers())
    .function("GetDataType", &vtkDoubleArray::GetDataType)
    .function("GetValue", &vtkDoubleArray::GetValue)
    .function("SetValue", &vtkDoubleArray::SetValue)
    .function("SetNumberOfValues", &vtkDoubleArray::SetNumberOfValues)
    .function("InsertValue", &vtkDoubleArray::InsertValue)
    .function("InsertNextValue", &vtkDoubleArray::InsertNextValue)
    .function("WritePointer", emscripten::optional_override([](vtkDoubleArray& self, int arg_0, int arg_1) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.WritePointer( arg_0, arg_1)) / sizeof(double);}))
    .function("GetPointer", emscripten::optional_override([](vtkDoubleArray& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetPointer( arg_0)) / sizeof(double);}))
    .function("SetArray", emscripten::select_overload<void(vtkDoubleArray&, std::uintptr_t, int, int)>([](vtkDoubleArray& self, std::uintptr_t arg_0, int arg_1, int arg_2) -> void { return self.SetArray(reinterpret_cast<double*>(arg_0 * sizeof(double)), arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("SetArray", emscripten::select_overload<void(vtkDoubleArray&, std::uintptr_t, int, int, int)>([](vtkDoubleArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void { return self.SetArray(reinterpret_cast<double*>(arg_0 * sizeof(double)), arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .class_function("FastDownCast", &vtkDoubleArray::FastDownCast, emscripten::allow_raw_pointers())
    .class_function("GetDataTypeValueMin", &vtkDoubleArray::GetDataTypeValueMin)
    .class_function("GetDataTypeValueMax", &vtkDoubleArray::GetDataTypeValueMax);
}
