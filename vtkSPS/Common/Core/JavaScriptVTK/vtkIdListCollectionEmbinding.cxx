// JavaScript wrapper for vtkIdListCollection with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkIdListCollectionEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkIdListCollection.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkIdList.h"
#include "vtkIdListCollection.h"

template<> void emscripten::internal::raw_destructor<vtkIdListCollection>(vtkIdListCollection * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkIdListCollection_class) {
  emscripten::class_<vtkIdListCollection, emscripten::base<vtkCollection>>("vtkIdListCollection")
    .smart_ptr<vtkSmartPointer<vtkIdListCollection>>("vtkSmartPointer<vtkIdListCollection>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkIdListCollection>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdListCollection::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkIdListCollection& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkIdListCollection::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkIdListCollection::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkIdListCollection::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkIdListCollection& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("AddItem", emscripten::select_overload<void(vtkIdListCollection&, vtkIdList*)>([](vtkIdListCollection& self, vtkIdList* arg_0) -> void { return self.AddItem( arg_0); }), emscripten::allow_raw_pointers())
    .function("GetNextItem", &vtkIdListCollection::GetNextItem, emscripten::allow_raw_pointers())
    .function("GetItem", &vtkIdListCollection::GetItem, emscripten::allow_raw_pointers());
}
