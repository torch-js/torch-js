#pragma once

#include <string>

#include <napi.h>

namespace torchjs {
namespace constants {
const static std::string kData = "data";
const static std::string kDtype = "dtype";
const static std::string kShape = "shape";

const static std::string kFloat32 = "float32";
const static std::string kFloat64 = "float64";
const static std::string kInt32 = "int32";

Napi::Object Init(Napi::Env env, Napi::Object exports);
} // namespace constants
} // namespace torchjs
