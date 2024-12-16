// JavaScript wrapper for vtkWindow with embind 
//
// This file was auto-generated using :
/*
node /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/bin/vtkWrapJavaScript.js \
 @/home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkCommonCore.js.Release.args \
 -o \
 /home/jmh/github/VTKCMake/build/library/VTK-prefix/src/VTK-build/CMakeFiles/vtkCommonCore.js/vtkWindowEmbinding.cxx \
 /home/jmh/github/vtk/Common/Core/vtkWindow.h
*/
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkEmbindUtils.h"
#include <emscripten.h>
#include <string>
#include "vtkVariant.h"
#include "vtkObjectBase.h"
#include "vtkIndent.h"
#include "vtkUnsignedCharArray.h"
#include "vtkWindow.h"

vtkAddDestructor(vtkWindow);
EMSCRIPTEN_BINDINGS(vtkWindow_class) {
  emscripten::class_<vtkWindow, emscripten::base<vtkObject>>("vtkWindow")
    .class_function("IsTypeOf", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkWindow::IsTypeOf( arg_0.c_str());}))
    .function("IsA", emscripten::optional_override([](vtkWindow& self, const std::string & arg_0) -> int {  return self.IsA( arg_0.c_str());}))
    .class_function("SafeDownCast", &vtkWindow::SafeDownCast, emscripten::allow_raw_pointers())
    .function("NewInstance", &vtkWindow::NewInstance, emscripten::allow_raw_pointers())
    .class_function("GetNumberOfGenerationsFromBaseType", emscripten::optional_override([]( const std::string & arg_0) -> int {  return vtkWindow::GetNumberOfGenerationsFromBaseType( arg_0.c_str());}))
    .function("GetNumberOfGenerationsFromBase", emscripten::optional_override([](vtkWindow& self, const std::string & arg_0) -> int {  return self.GetNumberOfGenerationsFromBase( arg_0.c_str());}))
    .function("SetDisplayId", emscripten::optional_override([](vtkWindow& self, std::uintptr_t arg_0) -> void {  return self.SetDisplayId(reinterpret_cast<void*>(arg_0));}))
    .function("SetWindowId", emscripten::optional_override([](vtkWindow& self, std::uintptr_t arg_0) -> void {  return self.SetWindowId(reinterpret_cast<void*>(arg_0));}))
    .function("SetParentId", emscripten::optional_override([](vtkWindow& self, std::uintptr_t arg_0) -> void {  return self.SetParentId(reinterpret_cast<void*>(arg_0));}))
    .function("GetGenericDisplayId", emscripten::optional_override([](vtkWindow& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetGenericDisplayId());}))
    .function("GetGenericWindowId", emscripten::optional_override([](vtkWindow& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetGenericWindowId());}))
    .function("GetGenericParentId", emscripten::optional_override([](vtkWindow& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetGenericParentId());}))
    .function("GetGenericContext", emscripten::optional_override([](vtkWindow& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetGenericContext());}))
    .function("GetGenericDrawable", emscripten::optional_override([](vtkWindow& self) -> std::uintptr_t {  return reinterpret_cast<std::uintptr_t>(self.GetGenericDrawable());}))
    .function("SetWindowInfo", emscripten::optional_override([](vtkWindow& self, const std::string & arg_0) -> void {  return self.SetWindowInfo( arg_0.c_str());}))
    .function("SetParentInfo", emscripten::optional_override([](vtkWindow& self, const std::string & arg_0) -> void {  return self.SetParentInfo( arg_0.c_str());}))
    .function("SetPosition", emscripten::select_overload<void(vtkWindow&, int, int)>([](vtkWindow& self, int arg_0, int arg_1) -> void { return self.SetPosition( arg_0, arg_1); }))
    .function("SetSize", emscripten::select_overload<void(vtkWindow&, int, int)>([](vtkWindow& self, int arg_0, int arg_1) -> void { return self.SetSize( arg_0, arg_1); }))
    .function("GetMapped", &vtkWindow::GetMapped)
    .function("GetShowWindow", &vtkWindow::GetShowWindow)
    .function("SetShowWindow", &vtkWindow::SetShowWindow)
    .function("ShowWindowOn", &vtkWindow::ShowWindowOn)
    .function("ShowWindowOff", &vtkWindow::ShowWindowOff)
    .function("SetUseOffScreenBuffers", &vtkWindow::SetUseOffScreenBuffers)
    .function("GetUseOffScreenBuffers", &vtkWindow::GetUseOffScreenBuffers)
    .function("UseOffScreenBuffersOn", &vtkWindow::UseOffScreenBuffersOn)
    .function("UseOffScreenBuffersOff", &vtkWindow::UseOffScreenBuffersOff)
    .function("SetErase", &vtkWindow::SetErase)
    .function("GetErase", &vtkWindow::GetErase)
    .function("EraseOn", &vtkWindow::EraseOn)
    .function("EraseOff", &vtkWindow::EraseOff)
    .function("SetDoubleBuffer", &vtkWindow::SetDoubleBuffer)
    .function("GetDoubleBuffer", &vtkWindow::GetDoubleBuffer)
    .function("DoubleBufferOn", &vtkWindow::DoubleBufferOn)
    .function("DoubleBufferOff", &vtkWindow::DoubleBufferOff)
    .function("GetWindowName", emscripten::optional_override([](vtkWindow& self) -> std::string {  return self.GetWindowName();}))
    .function("SetWindowName", emscripten::optional_override([](vtkWindow& self, const std::string & arg_0) -> void {  return self.SetWindowName( arg_0.c_str());}))
    .function("SetIcon", &vtkWindow::SetIcon, emscripten::allow_raw_pointers())
    .function("Render", &vtkWindow::Render)
    .function("ReleaseGraphicsResources", &vtkWindow::ReleaseGraphicsResources, emscripten::allow_raw_pointers())
    .function("GetPixelData", emscripten::select_overload<std::uintptr_t(vtkWindow&, int, int, int, int, int, int)>([](vtkWindow& self, int arg_0, int arg_1, int arg_2, int arg_3, int arg_4, int arg_5) -> std::uintptr_t { return reinterpret_cast<std::uintptr_t>(self.GetPixelData( arg_0, arg_1, arg_2, arg_3, arg_4, arg_5)); }))
    .function("GetPixelData", emscripten::select_overload<int(vtkWindow&, int, int, int, int, int, vtkUnsignedCharArray*, int)>([](vtkWindow& self, int arg_0, int arg_1, int arg_2, int arg_3, int arg_4, vtkUnsignedCharArray* arg_5, int arg_6) -> int { return self.GetPixelData( arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6); }), emscripten::allow_raw_pointers())
    .function("GetDPI", &vtkWindow::GetDPI)
    .function("SetDPI", &vtkWindow::SetDPI)
    .function("GetDPIMinValue", &vtkWindow::GetDPIMinValue)
    .function("GetDPIMaxValue", &vtkWindow::GetDPIMaxValue)
    .function("DetectDPI", &vtkWindow::DetectDPI)
    .function("SetOffScreenRendering", &vtkWindow::SetOffScreenRendering)
    .function("OffScreenRenderingOn", &vtkWindow::OffScreenRenderingOn)
    .function("OffScreenRenderingOff", &vtkWindow::OffScreenRenderingOff)
    .function("GetOffScreenRendering", &vtkWindow::GetOffScreenRendering)
    .function("MakeCurrent", &vtkWindow::MakeCurrent)
    .function("ReleaseCurrent", &vtkWindow::ReleaseCurrent)
    .function("SetTileScale", emscripten::select_overload<void(vtkWindow&, int, int)>([](vtkWindow& self, int arg_0, int arg_1) -> void { return self.SetTileScale( arg_0, arg_1); }))
    .function("SetTileScale", emscripten::select_overload<void(vtkWindow&, int)>([](vtkWindow& self, int arg_0) -> void { return self.SetTileScale( arg_0); }))
    .function("SetTileViewport", emscripten::select_overload<void(vtkWindow&, double, double, double, double)>([](vtkWindow& self, double arg_0, double arg_1, double arg_2, double arg_3) -> void { return self.SetTileViewport( arg_0, arg_1, arg_2, arg_3); }));
}
