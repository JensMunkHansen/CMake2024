// JavaScript wrapper for vtkScalarsToColors with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkScalarsToColorsEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkScalarsToColors.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkAbstractArray.h"
#include "vtkUnsignedCharArray.h"
#include "vtkDataArray.h"
#include "vtkStringArray.h"
#include "vtkStdString.h"
#include "vtkScalarsToColors.h"

EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkScalarsToColors_class_enums) {
}
template<> void emscripten::internal::raw_destructor<vtkScalarsToColors>(vtkScalarsToColors * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkScalarsToColors_class) {
  using VectorModes=vtkScalarsToColors::VectorModes;
  emscripten::class_<vtkScalarsToColors, emscripten::base<vtkObject>>("vtkScalarsToColors")
    .smart_ptr<vtkSmartPointer<vtkScalarsToColors>>("vtkSmartPointer<vtkScalarsToColors>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkScalarsToColors>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkScalarsToColors::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkScalarsToColors& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkScalarsToColors::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkScalarsToColors::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkScalarsToColors::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkScalarsToColors& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("IsOpaque", emscripten::select_overload<int(vtkScalarsToColors&)>([](vtkScalarsToColors& self) -> int { return self.IsOpaque(); }))
    .function("IsOpaque", emscripten::select_overload<int(vtkScalarsToColors&, vtkAbstractArray*, int, int)>([](vtkScalarsToColors& self, vtkAbstractArray* arg_0, int arg_1, int arg_2) -> int { return self.IsOpaque( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("IsOpaque", emscripten::select_overload<int(vtkScalarsToColors&, vtkAbstractArray*, int, int, vtkUnsignedCharArray*, unsigned char)>([](vtkScalarsToColors& self, vtkAbstractArray* arg_0, int arg_1, int arg_2, vtkUnsignedCharArray* arg_3, unsigned char arg_4) -> int { return self.IsOpaque( arg_0, arg_1, arg_2, arg_3, arg_4); }), emscripten::allow_raw_pointers())
    .function("Build", &vtkScalarsToColors::Build)
    .function("SetRange", emscripten::select_overload<void(vtkScalarsToColors&, double, double)>([](vtkScalarsToColors& self, double arg_0, double arg_1) -> void { return self.SetRange( arg_0, arg_1); }))
    .function("MapValue", emscripten::optional_override([](vtkScalarsToColors& self, double arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.MapValue( arg_0)) / sizeof(unsigned char);}))
    .function("GetOpacity", &vtkScalarsToColors::GetOpacity)
    .function("GetLuminance", &vtkScalarsToColors::GetLuminance)
    .function("SetAlpha", &vtkScalarsToColors::SetAlpha)
    .function("GetAlpha", &vtkScalarsToColors::GetAlpha)
    .function("MapScalars", emscripten::select_overload<vtkUnsignedCharArray*(vtkScalarsToColors&, vtkDataArray*, int, int, int)>([](vtkScalarsToColors& self, vtkDataArray* arg_0, int arg_1, int arg_2, int arg_3) -> vtkUnsignedCharArray* { return self.MapScalars( arg_0, arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .function("MapScalars", emscripten::select_overload<vtkUnsignedCharArray*(vtkScalarsToColors&, vtkAbstractArray*, int, int, int)>([](vtkScalarsToColors& self, vtkAbstractArray* arg_0, int arg_1, int arg_2, int arg_3) -> vtkUnsignedCharArray* { return self.MapScalars( arg_0, arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .function("SetVectorMode", &vtkScalarsToColors::SetVectorMode)
    .function("GetVectorMode", &vtkScalarsToColors::GetVectorMode)
    .function("SetVectorModeToMagnitude", &vtkScalarsToColors::SetVectorModeToMagnitude)
    .function("SetVectorModeToComponent", &vtkScalarsToColors::SetVectorModeToComponent)
    .function("SetVectorModeToRGBColors", &vtkScalarsToColors::SetVectorModeToRGBColors)
    .function("SetVectorComponent", &vtkScalarsToColors::SetVectorComponent)
    .function("GetVectorComponent", &vtkScalarsToColors::GetVectorComponent)
    .function("SetVectorSize", &vtkScalarsToColors::SetVectorSize)
    .function("GetVectorSize", &vtkScalarsToColors::GetVectorSize)
    .function("MapVectorsThroughTable", emscripten::select_overload<void(vtkScalarsToColors&, std::uintptr_t, std::uintptr_t, int, int, int, int, int, int)>([](vtkScalarsToColors& self, std::uintptr_t arg_0, std::uintptr_t arg_1, int arg_2, int arg_3, int arg_4, int arg_5, int arg_6, int arg_7) -> void { return self.MapVectorsThroughTable(reinterpret_cast<void*>(arg_0),reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2, arg_3, arg_4, arg_5, arg_6, arg_7); }))
    .function("MapVectorsThroughTable", emscripten::select_overload<void(vtkScalarsToColors&, std::uintptr_t, std::uintptr_t, int, int, int, int)>([](vtkScalarsToColors& self, std::uintptr_t arg_0, std::uintptr_t arg_1, int arg_2, int arg_3, int arg_4, int arg_5) -> void { return self.MapVectorsThroughTable(reinterpret_cast<void*>(arg_0),reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2, arg_3, arg_4, arg_5); }))
    .function("MapScalarsThroughTable", emscripten::select_overload<void(vtkScalarsToColors&, vtkDataArray*, std::uintptr_t, int)>([](vtkScalarsToColors& self, vtkDataArray* arg_0, std::uintptr_t arg_1, int arg_2) -> void { return self.MapScalarsThroughTable( arg_0,reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2); }), emscripten::allow_raw_pointers())
    .function("MapScalarsThroughTable", emscripten::select_overload<void(vtkScalarsToColors&, vtkDataArray*, std::uintptr_t)>([](vtkScalarsToColors& self, vtkDataArray* arg_0, std::uintptr_t arg_1) -> void { return self.MapScalarsThroughTable( arg_0,reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char))); }), emscripten::allow_raw_pointers())
    .function("MapScalarsThroughTable", emscripten::select_overload<void(vtkScalarsToColors&, std::uintptr_t, std::uintptr_t, int, int, int, int)>([](vtkScalarsToColors& self, std::uintptr_t arg_0, std::uintptr_t arg_1, int arg_2, int arg_3, int arg_4, int arg_5) -> void { return self.MapScalarsThroughTable(reinterpret_cast<void*>(arg_0),reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2, arg_3, arg_4, arg_5); }))
    .function("MapScalarsThroughTable2", emscripten::optional_override([](vtkScalarsToColors& self, std::uintptr_t arg_0, std::uintptr_t arg_1, int arg_2, int arg_3, int arg_4, int arg_5) -> void {  return self.MapScalarsThroughTable2(reinterpret_cast<void*>(arg_0),reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2, arg_3, arg_4, arg_5);}))
    .function("DeepCopy", &vtkScalarsToColors::DeepCopy, emscripten::allow_raw_pointers())
    .function("UsingLogScale", &vtkScalarsToColors::UsingLogScale)
    .function("GetNumberOfAvailableColors", &vtkScalarsToColors::GetNumberOfAvailableColors)
    .function("SetAnnotations", &vtkScalarsToColors::SetAnnotations, emscripten::allow_raw_pointers())
    .function("GetAnnotatedValues", &vtkScalarsToColors::GetAnnotatedValues, emscripten::allow_raw_pointers())
    .function("GetAnnotations", &vtkScalarsToColors::GetAnnotations, emscripten::allow_raw_pointers())
    .function("SetAnnotation", emscripten::select_overload<int(vtkScalarsToColors&, vtkVariant, vtkStdString)>([](vtkScalarsToColors& self, vtkVariant arg_0, vtkStdString arg_1) -> int { return self.SetAnnotation( arg_0, arg_1); }))
    .function("SetAnnotation", emscripten::select_overload<int(vtkScalarsToColors&, vtkStdString, vtkStdString)>([](vtkScalarsToColors& self, vtkStdString arg_0, vtkStdString arg_1) -> int { return self.SetAnnotation( arg_0, arg_1); }))
    .function("GetNumberOfAnnotatedValues", &vtkScalarsToColors::GetNumberOfAnnotatedValues)
    .function("GetAnnotatedValue", &vtkScalarsToColors::GetAnnotatedValue)
    .function("GetAnnotation", &vtkScalarsToColors::GetAnnotation)
    .function("GetAnnotatedValueIndex", &vtkScalarsToColors::GetAnnotatedValueIndex)
    .function("GetAnnotatedValueIndexInternal", &vtkScalarsToColors::GetAnnotatedValueIndexInternal)
    .function("RemoveAnnotation", &vtkScalarsToColors::RemoveAnnotation)
    .function("ResetAnnotations", &vtkScalarsToColors::ResetAnnotations)
    .function("SetIndexedLookup", &vtkScalarsToColors::SetIndexedLookup)
    .function("GetIndexedLookup", &vtkScalarsToColors::GetIndexedLookup)
    .function("IndexedLookupOn", &vtkScalarsToColors::IndexedLookupOn)
    .function("IndexedLookupOff", &vtkScalarsToColors::IndexedLookupOff);
}
EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkScalarsToColors_0_2_constants) {
    typedef vtkScalarsToColors::VectorModes cxx_enum_type;

  const struct { const char *name; cxx_enum_type value; }
    constants[3] = {
      { "vtkScalarsToColors_VectorModes_MAGNITUDE", vtkScalarsToColors::MAGNITUDE },
      { "vtkScalarsToColors_VectorModes_COMPONENT", vtkScalarsToColors::COMPONENT },
      { "vtkScalarsToColors_VectorModes_RGBCOLORS", vtkScalarsToColors::RGBCOLORS },
  };
  for (int c = 0; c < 3; c++)
  {
    emscripten::constant(constants[c].name, static_cast<int>(constants[c].value));
  }
}
