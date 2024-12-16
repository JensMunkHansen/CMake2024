// This is partly auto-generated using future Wrapping/JavaScript from KitWare
// JavaScript wrapper for vtkObjectBase with embind 
#include "vtkEmbindUtils.h"
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkIndent.h"
#include "vtkObjectBase.h"

vtkAddDestructor(vtkObjectBase);
EMSCRIPTEN_BINDINGS(vtkObjectBase_class) {
  emscripten::class_<vtkObjectBase>("vtkObjectBase")
    .smart_ptr<vtkSmartPointer<vtkObjectBase>>("vtkSmartPointer<vtkObjectBase>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkObjectBase>)
    .function("GetClassName", emscripten::optional_override([](vtkObjectBase& self) -> std::string {  return self.GetClassName();}))
    .function("GetObjectDescription", &vtkObjectBase::GetObjectDescription)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkObjectBase::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkObjectBase& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkObjectBase::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkObjectBase& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("InitializeObjectBase", &vtkObjectBase::InitializeObjectBase)
    .function("UsesGarbageCollector", &vtkObjectBase::UsesGarbageCollector)
    .function("GetReferenceCount", &vtkObjectBase::GetReferenceCount)
    .function("SetReferenceCount", &vtkObjectBase::SetReferenceCount);
}
