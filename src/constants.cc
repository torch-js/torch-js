#include "constants.h"

#include <torch/torch.h>

namespace torchjs {
namespace constants {
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(kFloat32, static_cast<int32_t>(torch::kFloat32));
  exports.Set(kFloat64, static_cast<int32_t>(torch::kFloat64));
  exports.Set(kInt32, static_cast<int32_t>(torch::kInt32));
  return exports;
}
} // namespace constants
} // namespace torchjs