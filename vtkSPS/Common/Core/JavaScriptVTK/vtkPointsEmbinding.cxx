// JavaScript wrapper for vtkPoints with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkPointsEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkPoints.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkDataArray.h"
#include "vtkIdList.h"
#include "vtkPoints.h"

template<> void emscripten::internal::raw_destructor<vtkPoints>(vtkPoints * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkPoints_class) {
  emscripten::class_<vtkPoints, emscripten::base<vtkObject>>("vtkPoints")
    .smart_ptr<vtkSmartPointer<vtkPoints>>("vtkSmartPointer<vtkPoints>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkPoints>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkPoints::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkPoints& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkPoints::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkPoints::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkPoints::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkPoints& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("Allocate", &vtkPoints::Allocate)
    .function("Initialize", &vtkPoints::Initialize)
    .function("SetData", &vtkPoints::SetData, emscripten::allow_raw_pointers())
    .function("GetData", &vtkPoints::GetData, emscripten::allow_raw_pointers())
    .function("GetDataType", &vtkPoints::GetDataType)
    .function("SetDataType", &vtkPoints::SetDataType)
    .function("SetDataTypeToBit", &vtkPoints::SetDataTypeToBit)
    .function("SetDataTypeToChar", &vtkPoints::SetDataTypeToChar)
    .function("SetDataTypeToUnsignedChar", &vtkPoints::SetDataTypeToUnsignedChar)
    .function("SetDataTypeToShort", &vtkPoints::SetDataTypeToShort)
    .function("SetDataTypeToUnsignedShort", &vtkPoints::SetDataTypeToUnsignedShort)
    .function("SetDataTypeToInt", &vtkPoints::SetDataTypeToInt)
    .function("SetDataTypeToUnsignedInt", &vtkPoints::SetDataTypeToUnsignedInt)
    .function("SetDataTypeToLong", &vtkPoints::SetDataTypeToLong)
    .function("SetDataTypeToUnsignedLong", &vtkPoints::SetDataTypeToUnsignedLong)
    .function("SetDataTypeToFloat", &vtkPoints::SetDataTypeToFloat)
    .function("SetDataTypeToDouble", &vtkPoints::SetDataTypeToDouble)
    .function("GetVoidPointer", emscripten::optional_override([](vtkPoints& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetVoidPointer( arg_0));}))
    .function("Squeeze", &vtkPoints::Squeeze)
    .function("Reset", &vtkPoints::Reset)
    .function("DeepCopy", &vtkPoints::DeepCopy, emscripten::allow_raw_pointers())
    .function("ShallowCopy", &vtkPoints::ShallowCopy, emscripten::allow_raw_pointers())
    .function("GetActualMemorySize", &vtkPoints::GetActualMemorySize)
    .function("GetNumberOfPoints", &vtkPoints::GetNumberOfPoints)
    .function("SetPoint", emscripten::select_overload<void(vtkPoints&, int, double, double, double)>([](vtkPoints& self, int arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.SetPoint( arg_0, arg_1, arg_2, arg_3); }))
    .function("GetPoint", emscripten::select_overload<emscripten::val(vtkPoints&, int)>([](vtkPoints &self, int index) -> emscripten::val {
      double* point = self.GetPoint(index);
	return emscripten::val(emscripten::typed_memory_view(3, point));}))
    .function("InsertPoint", emscripten::select_overload<void(vtkPoints&, int, double, double, double)>([](vtkPoints& self, int arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.InsertPoint( arg_0, arg_1, arg_2, arg_3); }))
    .function("InsertPoints", emscripten::select_overload<void(vtkPoints&, vtkIdList*, vtkIdList*, vtkPoints*)>([](vtkPoints& self, vtkIdList* arg_0, vtkIdList* arg_1, vtkPoints* arg_2) -> void { return self.InsertPoints( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("InsertPoints", emscripten::select_overload<void(vtkPoints&, int, int, int, vtkPoints*)>([](vtkPoints& self, int arg_0, int arg_1, int arg_2, vtkPoints* arg_3) -> void { return self.InsertPoints( arg_0, arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .function("InsertNextPoint", emscripten::select_overload<int(vtkPoints&, double, double, double)>([](vtkPoints& self, double arg_0, double arg_1, double arg_2) -> int { return self.InsertNextPoint( arg_0, arg_1, arg_2); }))
    .function("SetNumberOfPoints", &vtkPoints::SetNumberOfPoints)
    .function("Resize", &vtkPoints::Resize)
    .function("GetPoints", &vtkPoints::GetPoints, emscripten::allow_raw_pointers())
    .function("ComputeBounds", &vtkPoints::ComputeBounds)
    .function("GetMTime", &vtkPoints::GetMTime)
    .function("Modified", &vtkPoints::Modified);
}
