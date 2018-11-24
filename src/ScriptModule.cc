#include "ScriptModule.h"

#include "Tensor.h"
#include "utils.h"

namespace torchjs {

Napi::Object ScriptModule::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env, "ScriptModule",
                  {
                      InstanceMethod("forward", &ScriptModule::forward),
                      InstanceMethod("toString", &ScriptModule::toString),
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("ScriptModule", func);
  return exports;
}

ScriptModule::ScriptModule(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<ScriptModule>(info) {
  Napi::HandleScope scope(info.Env());
  Napi::String value = info[0].As<Napi::String>();
  path_ = value;
  module_ = torch::jit::load(value);
}

Napi::FunctionReference ScriptModule::constructor;

Napi::Value ScriptModule::forward(const Napi::CallbackInfo &info) {
  Napi::EscapableHandleScope scope(info.Env());
  auto len = info.Length();
  std::vector<torch::jit::IValue> inputs;
  // TODO: Support other type of IValue, e.g., list
  for (size_t i = 0; i < len; ++i) {
    Tensor *tensor =
        Napi::ObjectWrap<Tensor>::Unwrap(info[i].As<Napi::Object>());
    inputs.push_back(tensor->tensor());
  }
  auto outputs = module_->forward(inputs);
  // TODO: Support other type of IValue
  assert(outputs.isTensor());
  return scope.Escape(Tensor::FromTensor(info.Env(), outputs.toTensor()));
}

Napi::Value ScriptModule::toString(const Napi::CallbackInfo &info) {
  return Napi::String::New(info.Env(), "ScriptModule(\"" + path_ + "\")");
}

} // namespace torchjs