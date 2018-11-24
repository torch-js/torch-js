#pragma once

#include <napi.h>

namespace torchjs {
namespace aten {

Napi::Object Init(Napi::Env env, Napi::Object exports);

Napi::Value rand(const Napi::CallbackInfo &info);

} // namespace aten
} // namespace torchjs