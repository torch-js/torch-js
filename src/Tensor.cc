#include "Tensor.h"

#include "constants.h"
#include "utils.h"

namespace torchjs {

using namespace constants;

namespace {
template <typename T>
Napi::Value tensorToArray(Napi::Env env, const torch::Tensor &tensor) {
  Napi::EscapableHandleScope scope(env);
  assert(tensor.is_contiguous());
  auto typed_array = Napi::TypedArrayOf<T>::New(env, tensor.numel());
  memcpy(typed_array.Data(), tensor.data<T>(), sizeof(T) * tensor.numel());
  auto shape_array = tensorShapeToArray(env, tensor);
  auto obj = Napi::Object::New(env);
  obj.Set(kData, typed_array);
  obj.Set(kShape, shape_array);
  return scope.Escape(obj);
}

template <typename T>
Napi::Value arrayToTensor(Napi::Env env, const Napi::TypedArray &data,
                          const ShapeArrayType &shape_array) {
  Napi::EscapableHandleScope scope(env);
  auto *data_ptr = data.As<Napi::TypedArrayOf<T>>().Data();
  auto shape = shapeArrayToVector(shape_array);
  torch::TensorOptions options(scalarType<T>());
  auto torch_tensor = torch::empty(shape, options);
  memcpy(torch_tensor.data<T>(), data_ptr, sizeof(T) * torch_tensor.numel());
  return scope.Escape(Tensor::FromTensor(env, torch_tensor));
}
} // namespace

Napi::Object Tensor::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
      DefineClass(env, "Tensor",
                  {
                      InstanceMethod("toString", &Tensor::toString),
                      InstanceMethod("toObject", &Tensor::toObject),
                      StaticMethod("fromObject", &Tensor::fromObject),
                  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("Tensor", func);
  return exports;
}

Napi::Object Tensor::FromTensor(Napi::Env env, const torch::Tensor &tensor) {
  Napi::EscapableHandleScope scope(env);
  auto obj = constructor.New({});
  Napi::ObjectWrap<Tensor>::Unwrap(obj)->tensor_ = tensor;
  return scope.Escape(obj).ToObject();
}

Tensor::Tensor(const Napi::CallbackInfo &info) : ObjectWrap<Tensor>(info) {}

Napi::FunctionReference Tensor::constructor;

torch::Tensor Tensor::tensor() { return tensor_; }

Napi::Value Tensor::toString(const Napi::CallbackInfo &info) {
  return Napi::String::New(info.Env(), tensor_.toString());
}

Napi::Value Tensor::toObject(const Napi::CallbackInfo &info) {
  auto env = info.Env();
  auto st = tensor_.scalar_type();
  switch (st) {
  case torch::ScalarType::Float:
    return tensorToArray<float>(env, tensor_);
  case torch::ScalarType::Double:
    return tensorToArray<double>(env, tensor_);
  case torch::ScalarType::Int:
    return tensorToArray<int32_t>(env, tensor_);
  default:
    throw Napi::TypeError::New(env, "Unsupported type");
  }
}

Napi::Value Tensor::fromObject(const Napi::CallbackInfo &info) {
  auto env = info.Env();
  Napi::HandleScope scope(env);
  auto obj = info[0].As<Napi::Object>();
  auto data = obj.Get(kData).As<Napi::TypedArray>();
  auto shape = obj.Get(kShape).As<ShapeArrayType>();
  auto data_type = data.TypedArrayType();
  switch (data_type) {
  case napi_float32_array:
    return arrayToTensor<float>(env, data, shape);
  case napi_float64_array:
    return arrayToTensor<double>(env, data, shape);
  case napi_int32_array:
    return arrayToTensor<int32_t>(env, data, shape);
  default:
    throw Napi::TypeError::New(env, "Unsupported type");
  }
}

} // namespace torchjs