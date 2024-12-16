// JavaScript wrapper for vtkAbstractArray with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkAbstractArrayEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkAbstractArray.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkIdList.h"
#include "vtkArrayIterator.h"
#include "vtkVariantArray.h"
#include "vtkInformation.h"
#include "vtkInformationIntegerKey.h"
#include "vtkInformationInformationVectorKey.h"
#include "vtkInformationVariantVectorKey.h"
#include "vtkInformationDoubleVectorKey.h"
#include "vtkAbstractArray.h"

EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkAbstractArray_class_enums) {
}
template<> void emscripten::internal::raw_destructor<vtkAbstractArray>(vtkAbstractArray * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkAbstractArray_class) {
  using DeleteMethod=vtkAbstractArray::DeleteMethod;
  emscripten::class_<vtkAbstractArray, emscripten::base<vtkObject>>("vtkAbstractArray")
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkAbstractArray::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkAbstractArray& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkAbstractArray::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkAbstractArray::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkAbstractArray::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkAbstractArray& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .class_function("GetDataTypeSize", emscripten::select_overload<int( int)>([]( int arg_0) -> int { return vtkAbstractArray::GetDataTypeSize( arg_0); }))
    .function("SetNumberOfComponents", &vtkAbstractArray::SetNumberOfComponents)
    .function("GetNumberOfComponentsMinValue", &vtkAbstractArray::GetNumberOfComponentsMinValue)
    .function("GetNumberOfComponentsMaxValue", &vtkAbstractArray::GetNumberOfComponentsMaxValue)
    .function("GetNumberOfComponents", &vtkAbstractArray::GetNumberOfComponents)
    .function("SetComponentName", emscripten::optional_override([](vtkAbstractArray& self, int arg_0, const std::string & arg_1) -> void {  return self.SetComponentName( arg_0, arg_1.c_str());}))
    .function("GetComponentName", emscripten::optional_override([](vtkAbstractArray& self, int arg_0) -> std::string {  return self.GetComponentName( arg_0);}))
    .function("HasAComponentName", &vtkAbstractArray::HasAComponentName)
    .function("CopyComponentNames", &vtkAbstractArray::CopyComponentNames, emscripten::allow_raw_pointers())
    .function("SetNumberOfValues", &vtkAbstractArray::SetNumberOfValues)
    .function("GetNumberOfTuples", &vtkAbstractArray::GetNumberOfTuples)
    .function("GetNumberOfValues", &vtkAbstractArray::GetNumberOfValues)
    .function("GetTuples", emscripten::select_overload<void(vtkAbstractArray&, vtkIdList*, vtkAbstractArray*)>([](vtkAbstractArray& self, vtkIdList* arg_0, vtkAbstractArray* arg_1) -> void { return self.GetTuples( arg_0, arg_1); }), emscripten::allow_raw_pointers())
    .function("GetTuples", emscripten::select_overload<void(vtkAbstractArray&, int, int, vtkAbstractArray*)>([](vtkAbstractArray& self, int arg_0, int arg_1, vtkAbstractArray* arg_2) -> void { return self.GetTuples( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("HasStandardMemoryLayout", &vtkAbstractArray::HasStandardMemoryLayout)
    .function("DeepCopy", &vtkAbstractArray::DeepCopy, emscripten::allow_raw_pointers())
    .function("Reset", &vtkAbstractArray::Reset)
    .function("GetSize", &vtkAbstractArray::GetSize)
    .function("GetMaxId", &vtkAbstractArray::GetMaxId)
    .function("SetVoidArray", emscripten::select_overload<void(vtkAbstractArray&, std::uintptr_t, int, int, int)>([](vtkAbstractArray& self, std::uintptr_t arg_0, int arg_1, int arg_2, int arg_3) -> void { return self.SetVoidArray(reinterpret_cast<void*>(arg_0), arg_1, arg_2, arg_3); }))
    .function("ExportToVoidPointer", emscripten::optional_override([](vtkAbstractArray& self, std::uintptr_t arg_0) -> void {  return self.ExportToVoidPointer(reinterpret_cast<void*>(arg_0));}))
    .function("SetName", emscripten::optional_override([](vtkAbstractArray& self, const std::string & arg_0) -> void {  return self.SetName( arg_0.c_str());}))
    .function("GetName", emscripten::optional_override([](vtkAbstractArray& self) -> std::string {  return self.GetName();}))
    .function("GetDataTypeAsString", emscripten::optional_override([](vtkAbstractArray& self) -> std::string {  return self.GetDataTypeAsString();}))
    .class_function("CreateArray", &vtkAbstractArray::CreateArray, emscripten::allow_raw_pointers())
    .function("IsIntegral", &vtkAbstractArray::IsIntegral)
    .function("GetDataSize", &vtkAbstractArray::GetDataSize)
    .function("GetVariantValue", &vtkAbstractArray::GetVariantValue)
    .function("GetProminentComponentValues", &vtkAbstractArray::GetProminentComponentValues, emscripten::allow_raw_pointers())
    .function("GetInformation", &vtkAbstractArray::GetInformation, emscripten::allow_raw_pointers())
    .function("HasInformation", &vtkAbstractArray::HasInformation)
    .function("CopyInformation", &vtkAbstractArray::CopyInformation, emscripten::allow_raw_pointers())
    .class_function("GUI_HIDE", &vtkAbstractArray::GUI_HIDE, emscripten::allow_raw_pointers())
    .class_function("PER_COMPONENT", &vtkAbstractArray::PER_COMPONENT, emscripten::allow_raw_pointers())
    .class_function("PER_FINITE_COMPONENT", &vtkAbstractArray::PER_FINITE_COMPONENT, emscripten::allow_raw_pointers())
    .function("Modified", &vtkAbstractArray::Modified)
    .class_function("DISCRETE_VALUES", &vtkAbstractArray::DISCRETE_VALUES, emscripten::allow_raw_pointers())
    .class_function("DISCRETE_VALUE_SAMPLE_PARAMETERS", &vtkAbstractArray::DISCRETE_VALUE_SAMPLE_PARAMETERS, emscripten::allow_raw_pointers())
    .function("GetMaxDiscreteValues", &vtkAbstractArray::GetMaxDiscreteValues)
    .function("SetMaxDiscreteValues", &vtkAbstractArray::SetMaxDiscreteValues)
    .function("GetArrayType", &vtkAbstractArray::GetArrayType)
    .function("GetArrayTypeAsString", emscripten::optional_override([](vtkAbstractArray& self) -> std::string {  return self.GetArrayTypeAsString();}));
}
EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkAbstractArray_0_2_constants) {
    typedef vtkAbstractArray::DeleteMethod cxx_enum_type;

  const struct { const char *name; cxx_enum_type value; }
    constants[4] = {
      { "vtkAbstractArray_DeleteMethod_VTK_DATA_ARRAY_FREE", vtkAbstractArray::VTK_DATA_ARRAY_FREE },
      { "vtkAbstractArray_DeleteMethod_VTK_DATA_ARRAY_DELETE", vtkAbstractArray::VTK_DATA_ARRAY_DELETE },
      { "vtkAbstractArray_DeleteMethod_VTK_DATA_ARRAY_ALIGNED_FREE", vtkAbstractArray::VTK_DATA_ARRAY_ALIGNED_FREE },
      { "vtkAbstractArray_DeleteMethod_VTK_DATA_ARRAY_USER_DEFINED", vtkAbstractArray::VTK_DATA_ARRAY_USER_DEFINED },
  };
  for (int c = 0; c < 4; c++)
  {
    emscripten::constant(constants[c].name, static_cast<int>(constants[c].value));
  }
}
EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkAbstractArray_1_2_constants) {
  const struct { const char *name; int value; }
    constants[10] = {
      { "vtkAbstractArray_MAX_DISCRETE_VALUES", vtkAbstractArray::MAX_DISCRETE_VALUES },
      { "vtkAbstractArray_AbstractArray", vtkAbstractArray::AbstractArray },
      { "vtkAbstractArray_DataArray", vtkAbstractArray::DataArray },
      { "vtkAbstractArray_AoSDataArrayTemplate", vtkAbstractArray::AoSDataArrayTemplate },
      { "vtkAbstractArray_SoADataArrayTemplate", vtkAbstractArray::SoADataArrayTemplate },
      { "vtkAbstractArray_TypedDataArray", vtkAbstractArray::TypedDataArray },
      { "vtkAbstractArray_MappedDataArray", vtkAbstractArray::MappedDataArray },
      { "vtkAbstractArray_ScaleSoADataArrayTemplate", vtkAbstractArray::ScaleSoADataArrayTemplate },
      { "vtkAbstractArray_ImplicitArray", vtkAbstractArray::ImplicitArray },
      { "vtkAbstractArray_DataArrayTemplate", vtkAbstractArray::DataArrayTemplate },
  };
  for (int c = 0; c < 10; c++)
  {
    emscripten::constant(constants[c].name, constants[c].value);
  }
}
