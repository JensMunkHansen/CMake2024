// JavaScript wrapper for vtkVariant with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkVariantEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkVariant.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkStdString.h"
#include "vtkObjectBase.h"
#include "vtkAbstractArray.h"
#include "vtkVariant.h"

EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkVariant_class_enums) {
}

EMSCRIPTEN_BINDINGS(vtkVariant_class) {
  using StringFormatting=vtkVariant::StringFormatting;
  emscripten::class_<vtkVariant>("vtkVariant")
    .smart_ptr<std::shared_ptr<vtkVariant>>("std::shared_ptr<vtkVariant>")
    .constructor(&std::make_shared<vtkVariant>)
    .function("IsValid", &vtkVariant::IsValid)
    .function("IsString", &vtkVariant::IsString)
    .function("IsNumeric", &vtkVariant::IsNumeric)
    .function("IsFloat", &vtkVariant::IsFloat)
    .function("IsDouble", &vtkVariant::IsDouble)
    .function("IsChar", &vtkVariant::IsChar)
    .function("IsUnsignedChar", &vtkVariant::IsUnsignedChar)
    .function("IsSignedChar", &vtkVariant::IsSignedChar)
    .function("IsShort", &vtkVariant::IsShort)
    .function("IsUnsignedShort", &vtkVariant::IsUnsignedShort)
    .function("IsInt", &vtkVariant::IsInt)
    .function("IsUnsignedInt", &vtkVariant::IsUnsignedInt)
    .function("IsLong", &vtkVariant::IsLong)
    .function("IsUnsignedLong", &vtkVariant::IsUnsignedLong)
    .function("IsLongLong", &vtkVariant::IsLongLong)
    .function("IsUnsignedLongLong", &vtkVariant::IsUnsignedLongLong)
    .function("IsVTKObject", &vtkVariant::IsVTKObject)
    .function("IsArray", &vtkVariant::IsArray)
    .function("GetType", &vtkVariant::GetType)
    .function("GetTypeAsString", emscripten::optional_override([](vtkVariant& self) -> std::string {  return self.GetTypeAsString();}))
    .function("ToString", &vtkVariant::ToString)
    .function("ToFloat", emscripten::select_overload<float(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> float { return self.ToFloat(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToFloat", emscripten::select_overload<float(vtkVariant&)>([](vtkVariant& self) -> float { return self.ToFloat(); }))
    .function("ToDouble", emscripten::select_overload<double(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> double { return self.ToDouble(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToDouble", emscripten::select_overload<double(vtkVariant&)>([](vtkVariant& self) -> double { return self.ToDouble(); }))
    .function("ToChar", emscripten::select_overload<char(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> char { return self.ToChar(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToChar", emscripten::select_overload<char(vtkVariant&)>([](vtkVariant& self) -> char { return self.ToChar(); }))
    .function("ToUnsignedChar", emscripten::select_overload<unsigned char(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned char { return self.ToUnsignedChar(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToUnsignedChar", emscripten::select_overload<unsigned char(vtkVariant&)>([](vtkVariant& self) -> unsigned char { return self.ToUnsignedChar(); }))
    .function("ToSignedChar", emscripten::select_overload<signed char(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> signed char { return self.ToSignedChar(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToSignedChar", emscripten::select_overload<signed char(vtkVariant&)>([](vtkVariant& self) -> signed char { return self.ToSignedChar(); }))
    .function("ToShort", emscripten::select_overload<short(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> short { return self.ToShort(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToShort", emscripten::select_overload<short(vtkVariant&)>([](vtkVariant& self) -> short { return self.ToShort(); }))
    .function("ToUnsignedShort", emscripten::select_overload<unsigned short(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned short { return self.ToUnsignedShort(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToUnsignedShort", emscripten::select_overload<unsigned short(vtkVariant&)>([](vtkVariant& self) -> unsigned short { return self.ToUnsignedShort(); }))
    .function("ToInt", emscripten::select_overload<int(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> int { return self.ToInt(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToInt", emscripten::select_overload<int(vtkVariant&)>([](vtkVariant& self) -> int { return self.ToInt(); }))
    .function("ToUnsignedInt", emscripten::select_overload<unsigned int(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned int { return self.ToUnsignedInt(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToUnsignedInt", emscripten::select_overload<unsigned int(vtkVariant&)>([](vtkVariant& self) -> unsigned int { return self.ToUnsignedInt(); }))
    .function("ToLong", emscripten::select_overload<long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> long { return self.ToLong(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToLong", emscripten::select_overload<long(vtkVariant&)>([](vtkVariant& self) -> long { return self.ToLong(); }))
    .function("ToUnsignedLong", emscripten::select_overload<unsigned long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned long { return self.ToUnsignedLong(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToUnsignedLong", emscripten::select_overload<unsigned long(vtkVariant&)>([](vtkVariant& self) -> unsigned long { return self.ToUnsignedLong(); }))
    .function("ToLongLong", emscripten::select_overload<long long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> long long { return self.ToLongLong(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToLongLong", emscripten::select_overload<long long(vtkVariant&)>([](vtkVariant& self) -> long long { return self.ToLongLong(); }))
    .function("ToUnsignedLongLong", emscripten::select_overload<unsigned long long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned long long { return self.ToUnsignedLongLong(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToUnsignedLongLong", emscripten::select_overload<unsigned long long(vtkVariant&)>([](vtkVariant& self) -> unsigned long long { return self.ToUnsignedLongLong(); }))
    .function("ToTypeInt64", emscripten::select_overload<long long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> long long { return self.ToTypeInt64(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToTypeInt64", emscripten::select_overload<long long(vtkVariant&)>([](vtkVariant& self) -> long long { return self.ToTypeInt64(); }))
    .function("ToTypeUInt64", emscripten::select_overload<unsigned long long(vtkVariant&, std::uintptr_t)>([](vtkVariant& self, std::uintptr_t arg_0) -> unsigned long long { return self.ToTypeUInt64(reinterpret_cast<bool*>(arg_0 * sizeof(bool))); }))
    .function("ToTypeUInt64", emscripten::select_overload<unsigned long long(vtkVariant&)>([](vtkVariant& self) -> unsigned long long { return self.ToTypeUInt64(); }))
    .function("ToVTKObject", &vtkVariant::ToVTKObject, emscripten::allow_raw_pointers())
    .function("ToArray", &vtkVariant::ToArray, emscripten::allow_raw_pointers())
    .function("IsEqual", &vtkVariant::IsEqual);
}
EMSCRIPTEN_BINDINGS(vtkCommonCore_vtkVariant_0_2_constants) {
    typedef vtkVariant::StringFormatting cxx_enum_type;

  const struct { const char *name; cxx_enum_type value; }
    constants[3] = {
      { "vtkVariant_StringFormatting_DEFAULT_FORMATTING", vtkVariant::DEFAULT_FORMATTING },
      { "vtkVariant_StringFormatting_FIXED_FORMATTING", vtkVariant::FIXED_FORMATTING },
      { "vtkVariant_StringFormatting_SCIENTIFIC_FORMATTING", vtkVariant::SCIENTIFIC_FORMATTING },
  };
  for (int c = 0; c < 3; c++)
  {
    emscripten::constant(constants[c].name, static_cast<int>(constants[c].value));
  }
}

EMSCRIPTEN_BINDINGS(vtkVariantLessThan_class) {
  emscripten::class_<vtkVariantLessThan>("vtkVariantLessThan");
}

EMSCRIPTEN_BINDINGS(vtkVariantEqual_class) {
  emscripten::class_<vtkVariantEqual>("vtkVariantEqual");
}

EMSCRIPTEN_BINDINGS(vtkVariantStrictWeakOrder_class) {
  emscripten::class_<vtkVariantStrictWeakOrder>("vtkVariantStrictWeakOrder");
}

EMSCRIPTEN_BINDINGS(vtkVariantStrictEquality_class) {
  emscripten::class_<vtkVariantStrictEquality>("vtkVariantStrictEquality");
}
