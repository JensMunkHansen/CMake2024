// JavaScript wrapper for vtkIdList with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkIdListEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkIdList.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkIdList.h"

template<> void emscripten::internal::raw_destructor<vtkIdList>(vtkIdList * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkIdList_class) {
  emscripten::class_<vtkIdList, emscripten::base<vtkObject>>("vtkIdList")
    .smart_ptr<vtkSmartPointer<vtkIdList>>("vtkSmartPointer<vtkIdList>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkIdList>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdList::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkIdList& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkIdList::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkIdList::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdList::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkIdList& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("Initialize", &vtkIdList::Initialize)
    .function("Allocate", &vtkIdList::Allocate)
    .function("GetNumberOfIds", &vtkIdList::GetNumberOfIds)
    .function("GetId", &vtkIdList::GetId)
    .function("FindIdLocation", &vtkIdList::FindIdLocation)
    .function("SetNumberOfIds", &vtkIdList::SetNumberOfIds)
    .function("SetId", &vtkIdList::SetId)
    .function("InsertId", &vtkIdList::InsertId)
    .function("InsertNextId", &vtkIdList::InsertNextId)
    .function("InsertUniqueId", &vtkIdList::InsertUniqueId)
    .function("Sort", &vtkIdList::Sort)
    .function("Fill", &vtkIdList::Fill)
    .function("GetPointer", emscripten::optional_override([](vtkIdList& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetPointer( arg_0)) / sizeof(int);}))
    .function("WritePointer", emscripten::optional_override([](vtkIdList& self, int arg_0, int arg_1) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.WritePointer( arg_0, arg_1)) / sizeof(int);}))
    .function("SetArray", emscripten::optional_override([](vtkIdList& self, std::uintptr_t arg_0, int arg_1, bool arg_2) -> void {  return self.SetArray(reinterpret_cast<int*>(arg_0 * sizeof(int)), arg_1, arg_2);}))
    .function("Reset", &vtkIdList::Reset)
    .function("Squeeze", &vtkIdList::Squeeze)
    .function("DeepCopy", &vtkIdList::DeepCopy, emscripten::allow_raw_pointers())
    .function("DeleteId", &vtkIdList::DeleteId)
    .function("IsId", &vtkIdList::IsId)
    .function("IntersectWith", &vtkIdList::IntersectWith, emscripten::allow_raw_pointers())
    .function("Resize", emscripten::optional_override([](vtkIdList& self, int arg_0) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.Resize( arg_0)) / sizeof(int);}))
    .function("begin", emscripten::select_overload<std::uintptr_t(vtkIdList&)>([](vtkIdList& self) -> std::uintptr_t { return reinterpret_cast<std::uintptr_t>(self.begin()); }))
    .function("begin", emscripten::select_overload<std::uintptr_t(vtkIdList&)>([](vtkIdList& self) -> std::uintptr_t { return reinterpret_cast<std::uintptr_t>(self.begin()); }))
    .function("end", emscripten::select_overload<std::uintptr_t(vtkIdList&)>([](vtkIdList& self) -> std::uintptr_t { return reinterpret_cast<std::uintptr_t>(self.end()); }))
    .function("end", emscripten::select_overload<std::uintptr_t(vtkIdList&)>([](vtkIdList& self) -> std::uintptr_t { return reinterpret_cast<std::uintptr_t>(self.end()); }));
}
