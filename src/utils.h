#pragma once

#include <napi.h>
#include <torch/torch.h>

namespace torchjs {

// TODO: Switch to Napi::BigIntArray when it's more stable
using ShapeArrayType = Napi::Array;

ShapeArrayType tensorShapeToArray(Napi::Env, const torch::Tensor &);
std::vector<int64_t> shapeArrayToVector(const ShapeArrayType &);

template <typename T> torch::ScalarType scalarType();

} // namespace torchjs