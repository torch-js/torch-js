#include <napi.h>

#include "ATen.h"
#include "ScriptModule.h"
#include "Tensor.h"
#include "constants.h"

using namespace torchjs;

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  aten::Init(env, exports);
  constants::Init(env, exports);
  ScriptModule::Init(env, exports);
  Tensor::Init(env, exports);
  return exports;
}

NODE_API_MODULE(JSTorch, Init);