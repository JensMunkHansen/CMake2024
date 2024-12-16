// JavaScript wrapper for vtkVariantArray with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkVariantArrayEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkVariantArray.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkAbstractArray.h"
#include "vtkIdList.h"
#include "vtkArrayIterator.h"
#include "vtkVariantArray.h"

EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkVariantArray_class_enums) {
}
template<> void emscripten::internal::raw_destructor<vtkVariantArray>(vtkVariantArray * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkVariantArray_class) {
  using DeleteMethod=vtkVariantArray::DeleteMethod;
  emscripten::class_<vtkVariantArray, emscripten::base<vtkAbstractArray>>("vtkVariantArray")
    .smart_ptr<vtkSmartPointer<vtkVariantArray>>("vtkSmartPointer<vtkVariantArray>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkVariantArray>)
    .class_function("ExtendedNew", &vtkVariantArray::ExtendedNew, emscripten::allow_raw_pointers())
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkVariantArray::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkVariantArray& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkVariantArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkVariantArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkVariantArray::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkVariantArray& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("Allocate", &vtkVariantArray::Allocate)
    .function("Initialize", &vtkVariantArray::Initialize)
    .function("GetDataType", &vtkVariantArray::GetDataType)
    .function("GetDataTypeSize", &vtkVariantArray::GetDataTypeSize)
    .function("GetElementComponentSize", &vtkVariantArray::GetElementComponentSize)
    .function("SetNumberOfTuples", &vtkVariantArray::SetNumberOfTuples)
    .function("SetTuple", &vtkVariantArray::SetTuple, emscripten::allow_raw_pointers())
    .function("InsertTuple", &vtkVariantArray::InsertTuple, emscripten::allow_raw_pointers())
    .function("InsertTuples", emscripten::select_overload<void(vtkVariantArray&, vtkIdList*, vtkIdList*, vtkAbstractArray*)>([](vtkVariantArray& self, vtkIdList* arg_0, vtkIdList* arg_1, vtkAbstractArray* arg_2) -> void { return self.InsertTuples( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("InsertTuples", emscripten::select_overload<void(vtkVariantArray&, int, int, int, vtkAbstractArray*)>([](vtkVariantArray& self, int arg_0, int arg_1, int arg_2, vtkAbstractArray* arg_3) -> void { return self.InsertTuples( arg_0, arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .function("InsertTuplesStartingAt", &vtkVariantArray::InsertTuplesStartingAt, emscripten::allow_raw_pointers())
    .function("InsertNextTuple", &vtkVariantArray::InsertNextTuple, emscripten::allow_raw_pointers())
    .function("GetVoidPointer", emscripten::optional_override([](vtkVariantArray& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetVoidPointer( arg_0));}))
    .function("DeepCopy", &vtkVariantArray::DeepCopy, emscripten::allow_raw_pointers())
    .function("InterpolateTuple", emscripten::select_overload<void(vtkVariantArray&, int, vtkIdList*, vtkAbstractArray*, std::uintptr_t)>([](vtkVariantArray& self, int arg_0, vtkIdList* arg_1, vtkAbstractArray* arg_2, std::uintptr_t arg_3) -> void { return self.InterpolateTuple( arg_0, arg_1, arg_2,reinterpret_cast<double*>(arg_3 * sizeof(double))); }), emscripten::allow_raw_pointers())
    .function("InterpolateTuple", emscripten::select_overload<void(vtkVariantArray&, int, int, vtkAbstractArray*, int, vtkAbstractArray*, double)>([](vtkVariantArray& self, int arg_0, int arg_1, vtkAbstractArray* arg_2, int arg_3, vtkAbstractArray* arg_4, double arg_5) -> void { return self.InterpolateTuple( arg_0, arg_1, arg_2, arg_3, arg_4, arg_5); }), emscripten::allow_raw_pointers())
    .function("Squeeze", &vtkVariantArray::Squeeze)
    .function("Resize", &vtkVariantArray::Resize)
    .function("SetVoidArray", emscripten::select_overload<void(vtkVariantArray&, std::uintptr_t, int, int)>([](vtkVariantArray& self, std::uintptr_t arg_0, int arg_1, int arg_2) -> void { return self.SetVoidArray(reinterpret_cast<void*>(arg_0), arg_1, arg_2); }))
    .function("SetVoidArray", emscripten::select_overload<void(vtkVariantArray&, std::uintptr_t, int, int, int)>([](vtkVariantArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void { return self.SetVoidArray(reinterpret_cast<void*>(arg_0), arg_1, arg_2, arg_3); }))
    .function("GetActualMemorySize", &vtkVariantArray::GetActualMemorySize)
    .function("IsNumeric", &vtkVariantArray::IsNumeric)
    .function("NewIterator", &vtkVariantArray::NewIterator, emscripten::allow_raw_pointers())
    .function("SetValue", &vtkVariantArray::SetValue)
    .function("InsertValue", &vtkVariantArray::InsertValue)
    .function("SetVariantValue", &vtkVariantArray::SetVariantValue)
    .function("InsertVariantValue", &vtkVariantArray::InsertVariantValue)
    .function("InsertNextValue", &vtkVariantArray::InsertNextValue)
    .function("SetArrayFreeFunction", emscripten::optional_override([](vtkVariantArray& self, emscripten::val arg_0) -> void {  return self.SetArrayFreeFunction( reinterpret_cast<void(*)( void*)>(emscripten::val::module_property("addFunction")(arg_0, std::string("vi")).as<int>()));}))
    .function("GetNumberOfValues", &vtkVariantArray::GetNumberOfValues)
    .function("LookupValue", emscripten::select_overload<int(vtkVariantArray&, vtkVariant)>([](vtkVariantArray& self, vtkVariant arg_0) -> int { return self.LookupValue( arg_0); }))
    .function("LookupValue", emscripten::select_overload<void(vtkVariantArray&, vtkVariant, vtkIdList*)>([](vtkVariantArray& self, vtkVariant arg_0, vtkIdList* arg_1) -> void { return self.LookupValue( arg_0, arg_1); }), emscripten::allow_raw_pointers())
    .function("DataChanged", &vtkVariantArray::DataChanged)
    .function("DataElementChanged", &vtkVariantArray::DataElementChanged)
    .function("ClearLookup", &vtkVariantArray::ClearLookup);
}
EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkVariantArray_0_2_constants) {
    typedef vtkVariantArray::DeleteMethod cxx_enum_type;

  const struct { const char *name; cxx_enum_type value; }
    constants[4] = {
      { "vtkVariantArray_DeleteMethod_VTK_DATA_ARRAY_FREE", vtkVariantArray::VTK_DATA_ARRAY_FREE },
      { "vtkVariantArray_DeleteMethod_VTK_DATA_ARRAY_DELETE", vtkVariantArray::VTK_DATA_ARRAY_DELETE },
      { "vtkVariantArray_DeleteMethod_VTK_DATA_ARRAY_ALIGNED_FREE", vtkVariantArray::VTK_DATA_ARRAY_ALIGNED_FREE },
      { "vtkVariantArray_DeleteMethod_VTK_DATA_ARRAY_USER_DEFINED", vtkVariantArray::VTK_DATA_ARRAY_USER_DEFINED },
  };
  for (int c = 0; c < 4; c++)
  {
    emscripten::constant(constants[c].name, static_cast<int>(constants[c].value));
  }
}
