// JavaScript wrapper for vtkRandomPool with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkRandomPoolEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkRandomPool.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkRandomSequence.h"
#include "vtkDataArray.h"
#include "vtkRandomPool.h"

template<> void emscripten::internal::raw_destructor<vtkRandomPool>(vtkRandomPool * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkRandomPool_class) {
  emscripten::class_<vtkRandomPool, emscripten::base<vtkObject>>("vtkRandomPool")
    .smart_ptr<vtkSmartPointer<vtkRandomPool>>("vtkSmartPointer<vtkRandomPool>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkRandomPool>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkRandomPool::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkRandomPool& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkRandomPool::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkRandomPool::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkRandomPool::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkRandomPool& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("SetSequence", &vtkRandomPool::SetSequence, emscripten::allow_raw_pointers())
    .function("GetSequence", &vtkRandomPool::GetSequence, emscripten::allow_raw_pointers())
    .function("SetSize", &vtkRandomPool::SetSize)
    .function("GetSizeMinValue", &vtkRandomPool::GetSizeMinValue)
    .function("GetSizeMaxValue", &vtkRandomPool::GetSizeMaxValue)
    .function("GetSize", &vtkRandomPool::GetSize)
    .function("SetNumberOfComponents", &vtkRandomPool::SetNumberOfComponents)
    .function("GetNumberOfComponentsMinValue", &vtkRandomPool::GetNumberOfComponentsMinValue)
    .function("GetNumberOfComponentsMaxValue", &vtkRandomPool::GetNumberOfComponentsMaxValue)
    .function("GetNumberOfComponents", &vtkRandomPool::GetNumberOfComponents)
    .function("GetTotalSize", &vtkRandomPool::GetTotalSize)
    .function("GeneratePool", emscripten::optional_override([](vtkRandomPool& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GeneratePool()) / sizeof(double);}))
    .function("GetPool", emscripten::optional_override([](vtkRandomPool& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetPool()) / sizeof(double);}))
    .function("GetValue", emscripten::select_overload<double(vtkRandomPool&, int)>([](vtkRandomPool& self, int arg_0) -> double { return self.GetValue( arg_0); }))
    .function("GetValue", emscripten::select_overload<double(vtkRandomPool&, int, int)>([](vtkRandomPool& self, int arg_0, int arg_1) -> double { return self.GetValue( arg_0, arg_1); }))
    .function("PopulateDataArray", emscripten::select_overload<void(vtkRandomPool&, vtkDataArray*, double, double)>([](vtkRandomPool& self, vtkDataArray* arg_0, double arg_1, double arg_2) -> void { return self.PopulateDataArray( arg_0, arg_1, arg_2); }), emscripten::allow_raw_pointers())
    .function("PopulateDataArray", emscripten::select_overload<void(vtkRandomPool&, vtkDataArray*, int, double, double)>([](vtkRandomPool& self, vtkDataArray* arg_0, int arg_1, double arg_2, double arg_3) -> void { return self.PopulateDataArray( arg_0, arg_1, arg_2, arg_3); }), emscripten::allow_raw_pointers())
    .function("SetChunkSize", &vtkRandomPool::SetChunkSize)
    .function("GetChunkSizeMinValue", &vtkRandomPool::GetChunkSizeMinValue)
    .function("GetChunkSizeMaxValue", &vtkRandomPool::GetChunkSizeMaxValue)
    .function("GetChunkSize", &vtkRandomPool::GetChunkSize);
}
