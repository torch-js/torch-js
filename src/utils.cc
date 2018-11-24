#include "utils.h"

#include "constants.h"

namespace torchjs {

using namespace constants;

torch::TensorOptions parseTensorOptions(const Napi::Object &obj) {
  torch::TensorOptions options;
  if (obj.Has(kDtype)) {
    options = options.dtype(static_cast<torch::ScalarType>(
        obj.Get(kDtype).As<Napi::Number>().Int32Value()));
  }
  return options;
}

ShapeArrayType tensorShapeToArray(Napi::Env env, const torch::Tensor &tensor) {
  Napi::EscapableHandleScope scope(env);
  auto shape = tensor.sizes();
  auto shape_array = ShapeArrayType::New(env, shape.size());
  // Int64 is not well supported in N-API so this can't be memcpy'ed
  for (size_t i = 0; i < shape.size(); ++i) {
    shape_array[i] = shape[i];
  }
  return scope.Escape(shape_array).As<ShapeArrayType>();
}

std::vector<int64_t> shapeArrayToVector(const ShapeArrayType &size_array) {
  auto array_len = size_array.Length();
  std::vector<int64_t> sizes;
  for (decltype(array_len) i = 0; i < array_len; ++i) {
    Napi::HandleScope scope(size_array.Env());
    sizes.push_back(static_cast<Napi::Value>(size_array[i])
                        .As<Napi::Number>()
                        .Int64Value());
  }
  return sizes;
}

template <> torch::ScalarType scalarType<float>() { return torch::kFloat32; }
template <> torch::ScalarType scalarType<double>() { return torch::kFloat64; }
template <> torch::ScalarType scalarType<int32_t>() { return torch::kInt32; }
template <> torch::ScalarType scalarType<int64_t>() { return torch::kInt64; }

} // namespace torchjs