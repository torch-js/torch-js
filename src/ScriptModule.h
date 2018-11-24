#pragma once

#include <memory>

#include <napi.h>
#include <torch/script.h>

namespace torchjs {

/**
 * Wrapper type on torch::jit::script::Module
 *
 * The loaded module should return only one torch::Tensor
 **/
class ScriptModule : public Napi::ObjectWrap<ScriptModule> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  /**
   * Take one input; the path to the module to load
   **/
  ScriptModule(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;
  std::shared_ptr<torch::jit::script::Module> module_;
  std::string path_;
  /**
   * This can be called with a variable number of input Tensors.
   **/
  Napi::Value forward(const Napi::CallbackInfo &info);
  Napi::Value toString(const Napi::CallbackInfo &info);
};

} // namespace torchjs