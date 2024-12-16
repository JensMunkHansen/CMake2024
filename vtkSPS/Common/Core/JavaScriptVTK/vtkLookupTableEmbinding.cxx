// JavaScript wrapper for vtkLookupTable with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkLookupTableEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkLookupTable.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkAbstractArray.h"
#include "vtkUnsignedCharArray.h"
#include "vtkScalarsToColors.h"
#include "vtkLookupTable.h"

EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkLookupTable_0_1_constants) {
  const struct { const char *name; int value; }
    constants[5] = {
      { "VTK_RAMP_LINEAR", 0 },
      { "VTK_RAMP_SCURVE", 1 },
      { "VTK_RAMP_SQRT", 2 },
      { "VTK_SCALE_LINEAR", 0 },
      { "VTK_SCALE_LOG10", 1 },
  };
  for (int c = 0; c < 5; c++)
  {
    emscripten::constant(constants[c].name, constants[c].value);
  }
}
template<> void emscripten::internal::raw_destructor<vtkLookupTable>(vtkLookupTable * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkLookupTable_class) {
  emscripten::class_<vtkLookupTable, emscripten::base<vtkScalarsToColors>>("vtkLookupTable")
    .smart_ptr<vtkSmartPointer<vtkLookupTable>>("vtkSmartPointer<vtkLookupTable>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkLookupTable>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkLookupTable::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkLookupTable& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkLookupTable::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkLookupTable::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkLookupTable::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkLookupTable& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("IsOpaque", emscripten::select_overload<int(vtkLookupTable&)>([](vtkLookupTable& self) -> int { return self.IsOpaque(); }))
    .function("IsOpaque", emscripten::select_overload<int(vtkLookupTable&, vtkAbstractArray*, int, int)>([](vtkLookupTable& self, vtkAbstractArray* arg_0, int arg_1, int arg_2) -> int { return self.IsOpaque( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("IsOpaque", emscripten::select_overload<int(vtkLookupTable&, vtkAbstractArray*, int, int, vtkUnsignedCharArray*, unsigned char)>([](vtkLookupTable& self, vtkAbstractArray* arg_0, int arg_1, int arg_2, vtkUnsignedCharArray* arg_3, unsigned char arg_4) -> int { return self.IsOpaque( arg_0, arg_1, arg_2, arg_3, arg_4); }), emscripten::allow_raw_pointers())
    .function("Allocate", &vtkLookupTable::Allocate)
    .function("Build", &vtkLookupTable::Build)
    .function("ForceBuild", &vtkLookupTable::ForceBuild)
    .function("BuildSpecialColors", &vtkLookupTable::BuildSpecialColors)
    .function("SetRamp", &vtkLookupTable::SetRamp)
    .function("SetRampToLinear", &vtkLookupTable::SetRampToLinear)
    .function("SetRampToSCurve", &vtkLookupTable::SetRampToSCurve)
    .function("SetRampToSQRT", &vtkLookupTable::SetRampToSQRT)
    .function("GetRamp", &vtkLookupTable::GetRamp)
    .function("SetScale", &vtkLookupTable::SetScale)
    .function("SetScaleToLinear", &vtkLookupTable::SetScaleToLinear)
    .function("SetScaleToLog10", &vtkLookupTable::SetScaleToLog10)
    .function("GetScale", &vtkLookupTable::GetScale)
    .function("SetTableRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetTableRange( arg_0, arg_1); }))
    .function("SetHueRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetHueRange( arg_0, arg_1); }))
    .function("SetSaturationRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetSaturationRange( arg_0, arg_1); }))
    .function("SetValueRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetValueRange( arg_0, arg_1); }))
    .function("SetAlphaRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetAlphaRange( arg_0, arg_1); }))
    .function("SetNanColor", emscripten::select_overload<void(vtkLookupTable&, double, double, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.SetNanColor( arg_0, arg_1, arg_2, arg_3); }))
    .function("GetNanColorAsUnsignedChars", emscripten::optional_override([](vtkLookupTable& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetNanColorAsUnsignedChars()) / sizeof(unsigned char);}))
    .function("SetBelowRangeColor", emscripten::select_overload<void(vtkLookupTable&, double, double, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.SetBelowRangeColor( arg_0, arg_1, arg_2, arg_3); }))
    .function("SetUseBelowRangeColor", &vtkLookupTable::SetUseBelowRangeColor)
    .function("GetUseBelowRangeColor", &vtkLookupTable::GetUseBelowRangeColor)
    .function("UseBelowRangeColorOn", &vtkLookupTable::UseBelowRangeColorOn)
    .function("UseBelowRangeColorOff", &vtkLookupTable::UseBelowRangeColorOff)
    .function("SetAboveRangeColor", emscripten::select_overload<void(vtkLookupTable&, double, double, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.SetAboveRangeColor( arg_0, arg_1, arg_2, arg_3); }))
    .function("SetUseAboveRangeColor", &vtkLookupTable::SetUseAboveRangeColor)
    .function("GetUseAboveRangeColor", &vtkLookupTable::GetUseAboveRangeColor)
    .function("UseAboveRangeColorOn", &vtkLookupTable::UseAboveRangeColorOn)
    .function("UseAboveRangeColorOff", &vtkLookupTable::UseAboveRangeColorOff)
    .function("MapValue", emscripten::optional_override([](vtkLookupTable& self, double arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.MapValue( arg_0)) / sizeof(unsigned char);}))
    .function("GetOpacity", &vtkLookupTable::GetOpacity)
    .function("GetIndex", &vtkLookupTable::GetIndex)
    .function("SetNumberOfTableValues", &vtkLookupTable::SetNumberOfTableValues)
    .function("GetNumberOfTableValues", &vtkLookupTable::GetNumberOfTableValues)
    .function("SetTableValue", emscripten::select_overload<void(vtkLookupTable&, int, double, double, double, double)>([](vtkLookupTable& self, int arg_0, double arg_1, double arg_2, double arg_3, double arg_4) -> void { return self.SetTableValue( arg_0, arg_1, arg_2, arg_3, arg_4); }))
    .function("GetPointer", emscripten::optional_override([](vtkLookupTable& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetPointer( arg_0)) / sizeof(unsigned char);}))
    .function("WritePointer", emscripten::optional_override([](vtkLookupTable& self, int arg_0, int arg_1) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.WritePointer( arg_0, arg_1)) / sizeof(unsigned char);}))
    .function("SetRange", emscripten::select_overload<void(vtkLookupTable&, double, double)>([](vtkLookupTable& self, double arg_0, double arg_1) -> void { return self.SetRange( arg_0, arg_1); }))
    .function("SetNumberOfColors", &vtkLookupTable::SetNumberOfColors)
    .function("GetNumberOfColorsMinValue", &vtkLookupTable::GetNumberOfColorsMinValue)
    .function("GetNumberOfColorsMaxValue", &vtkLookupTable::GetNumberOfColorsMaxValue)
    .function("GetNumberOfColors", &vtkLookupTable::GetNumberOfColors)
    .function("SetTable", &vtkLookupTable::SetTable, emscripten::allow_raw_pointers())
    .function("GetTable", &vtkLookupTable::GetTable, emscripten::allow_raw_pointers())
    .function("MapScalarsThroughTable2", emscripten::optional_override([](vtkLookupTable& self, std::uintptr_t arg_0, std::uintptr_t arg_1, int arg_2, int arg_3, int arg_4, int arg_5) -> void {  return self.MapScalarsThroughTable2(reinterpret_cast<void*>(arg_0),reinterpret_cast<unsigned char*>(arg_1 * sizeof(unsigned char)), arg_2, arg_3, arg_4, arg_5);}))
    .function("DeepCopy", &vtkLookupTable::DeepCopy, emscripten::allow_raw_pointers())
    .function("UsingLogScale", &vtkLookupTable::UsingLogScale)
    .function("GetNumberOfAvailableColors", &vtkLookupTable::GetNumberOfAvailableColors);
}
