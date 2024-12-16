// This is partly auto-generated using future Wrapping/JavaScript from KitWare
// JavaScript wrapper for vtkCallbackCommand with embind
#include "vtkCallbackCommand.h"
#include "vtkEmbindSmartPointerTraits.h"
#include "vtkEmbindUtils.h"
#include "vtkObject.h"
#include "vtkObjectBase.h"
#include "vtkVariant.h"
#include <emscripten.h>
#include <string>


vtkAddDestructor(vtkCallbackCommand);
EMSCRIPTEN_BINDINGS(vtkCallbackCommand_class)
{
    emscripten::class_<vtkCallbackCommand, emscripten::base<vtkCommand>>("vtkCallbackCommand")
      .smart_ptr<vtkSmartPointer<vtkCallbackCommand>>("vtkSmartPointer<vtkCallbackCommand>")
      .constructor(&vtk::MakeVTKSmartPtr<vtkCallbackCommand>)
      .class_function("IsTypeOf", emscripten::optional_override([](const std::string &arg_0) -> int {
          return vtkCallbackCommand::IsTypeOf(arg_0.c_str());
      }))
      .function("IsA", emscripten::optional_override([](vtkCallbackCommand &self, const std::string &arg_0) -> int {
          return self.IsA(arg_0.c_str());
      }))
      .class_function("SafeDownCast", &vtkCallbackCommand::SafeDownCast, emscripten::allow_raw_pointers())
      .function("NewInstance", &vtkCallbackCommand::NewInstance, emscripten::allow_raw_pointers())
      .class_function(
        "GetNumberOfGenerationsFromBaseType", emscripten::optional_override([](const std::string &arg_0) -> int {
            return vtkCallbackCommand::GetNumberOfGenerationsFromBaseType(arg_0.c_str());
        }))
      .function("GetNumberOfGenerationsFromBase",
        emscripten::optional_override([](vtkCallbackCommand &self, const std::string &arg_0) -> int {
            return self.GetNumberOfGenerationsFromBase(arg_0.c_str());
        }))
      .function("Execute",
        emscripten::optional_override(
          [](vtkCallbackCommand &self, vtkObject *arg_0, unsigned long arg_1, std::uintptr_t arg_2) -> void {
              return self.Execute(arg_0, arg_1, reinterpret_cast<void *>(arg_2));
          }),
        emscripten::allow_raw_pointers())
      .function(
        "SetClientData", emscripten::optional_override([](vtkCallbackCommand &self, std::uintptr_t arg_0) -> void {
            return self.SetClientData(reinterpret_cast<void *>(arg_0));
        }))
      .function("GetClientData", emscripten::optional_override([](vtkCallbackCommand &self) -> std::uintptr_t {
          return reinterpret_cast<std::uintptr_t>(self.GetClientData());
      }))
      .function(
        "SetCallback", emscripten::optional_override([](vtkCallbackCommand &self, emscripten::val arg_0) -> void {
            return self.SetCallback(reinterpret_cast<void (*)(vtkObject *, unsigned long, void *, void *)>(
              emscripten::val::module_property("addFunction")(arg_0, std::string("viiii")).as<int>()));
        }))
      .function("SetClientDataDeleteCallback",
        emscripten::optional_override([](vtkCallbackCommand &self, emscripten::val arg_0) -> void {
            return self.SetClientDataDeleteCallback(reinterpret_cast<void (*)(void *)>(
              emscripten::val::module_property("addFunction")(arg_0, std::string("vi")).as<int>()));
        }))
      .function("SetAbortFlagOnExecute", &vtkCallbackCommand::SetAbortFlagOnExecute)
      .function("GetAbortFlagOnExecute", &vtkCallbackCommand::GetAbortFlagOnExecute)
      .function("AbortFlagOnExecuteOn", &vtkCallbackCommand::AbortFlagOnExecuteOn)
      .function("AbortFlagOnExecuteOff", &vtkCallbackCommand::AbortFlagOnExecuteOff);
}
