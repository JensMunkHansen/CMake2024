// JavaScript wrapper for vtkCollection with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCollectionEmbinding.cxx \
 /home/jmh/wasm/vtk/Common/Core/vtkCollection.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkObject.h"
#include "vtkCollectionIterator.h"
#include "vtkCollection.h"


EMSCRIPTEN_BINDINGS(vtkCollectionElement_class) {
  emscripten::class_<vtkCollectionElement>("vtkCollectionElement");
}
template<> void emscripten::internal::raw_destructor<vtkCollection>(vtkCollection * ptr){ ptr->Delete(); }
EMSCRIPTEN_BINDINGS(vtkCollection_class) {
  emscripten::class_<vtkCollection, emscripten::base<vtkObject>>("vtkCollection")
    .smart_ptr<vtkSmartPointer<vtkCollection>>("vtkSmartPointer<vtkCollection>")
    .constructor(&vtk::MakeVTKSmartPtr<vtkCollection>)
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkCollection::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkCollection& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkCollection::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkCollection::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkCollection::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkCollection& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("AddItem", &vtkCollection::AddItem, emscripten::allow_raw_pointers())
    .function("InsertItem", &vtkCollection::InsertItem, emscripten::allow_raw_pointers())
    .function("ReplaceItem", &vtkCollection::ReplaceItem, emscripten::allow_raw_pointers())
    .function("RemoveItem", emscripten::select_overload<void(vtkCollection&, int)>([](vtkCollection& self, int arg_0) -> void { return self.RemoveItem( arg_0); }))
    .function("RemoveItem", emscripten::select_overload<void(vtkCollection&, vtkObject*)>([](vtkCollection& self, vtkObject* arg_0) -> void { return self.RemoveItem( arg_0); }), emscripten::allow_raw_pointers())
    .function("RemoveAllItems", &vtkCollection::RemoveAllItems)
    .function("IsItemPresent", &vtkCollection::IsItemPresent, emscripten::allow_raw_pointers())
    .function("IndexOfFirstOccurence", &vtkCollection::IndexOfFirstOccurence, emscripten::allow_raw_pointers())
    .function("GetNumberOfItems", &vtkCollection::GetNumberOfItems)
    .function("InitTraversal", emscripten::select_overload<void(vtkCollection&)>([](vtkCollection& self) -> void { return self.InitTraversal(); }))
    .function("GetNextItemAsObject", emscripten::select_overload<vtkObject*(vtkCollection&)>([](vtkCollection& self) -> vtkObject* { return self.GetNextItemAsObject(); }), emscripten::allow_raw_pointers())
    .function("GetItemAsObject", &vtkCollection::GetItemAsObject, emscripten::allow_raw_pointers())
    .function("NewIterator", &vtkCollection::NewIterator, emscripten::allow_raw_pointers())
    .function("UsesGarbageCollector", &vtkCollection::UsesGarbageCollector);
}
