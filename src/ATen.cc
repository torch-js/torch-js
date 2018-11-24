#include "ATen.h"

#include <torch/torch.h>

#include "Tensor.h"
#include "constants.h"
#include "utils.h"

namespace torchjs {

using namespace constants;

namespace aten {

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("rand", Napi::Function::New(env, rand));
  return exports;
}

Napi::Value rand(const Napi::CallbackInfo &info) {
  Napi::EscapableHandleScope scope(info.Env());
  auto len = info.Length();

  torch::TensorOptions options;
  if (len > 1 && info[len - 1].IsObject()) {
    auto option_obj = info[len - 1].As<Napi::Object>();
    options = parseTensorOptions(option_obj);
    --len;
  }

  std::vector<int64_t> sizes;

  // TODO: Support int64_t sizes
  if (len == 1 && info[0].IsArray()) {
    auto size_array = info[0].As<Napi::Array>();
    sizes = shapeArrayToVector(size_array);
  } else {
    for (size_t i = 0; i < len; ++i) {
      sizes.push_back(info[i].As<Napi::Number>().Int64Value());
    }
  }
  auto rand_tensor = torch::rand(sizes, options);
  return scope.Escape(Tensor::FromTensor(info.Env(), rand_tensor));
}

} // namespace aten
} // namespace torchjs