"use strict";
var torch = require("bindings")("torch-js");
const assert = require('assert');

function flattenArray(arr) {
  var shape = [arr.length];
  while (arr.length > 0 && Array.isArray(arr[0])) {
    shape.push(arr[0].length);
    arr = arr.reduce((acc, val) => acc.concat(val), []);;

    // Running assert in every step to make sure that shape is regular
    var numel = shape.reduce((acc, cur) => acc * cur);
    assert.strictEqual(arr.length, numel);
  }
  return {
    data: arr,
    shape: shape,
  }
}

function typedArrayType(options) {
  if (options === undefined || options.dtype === undefined) {
    return Float32Array;
  }
  switch (options.dtype) {
    case torch.float32:
      return Float32Array;
    case torch.float64:
      return Float64Array;
    case torch.int32:
      return Int32Array;
    default:
      throw new TypeError("Unsupported dtype");
  }
}

torch.tensor = (data, options) => {
  if (Array.isArray(data)) {
    var array_and_shape = flattenArray(data);
    var typed_array = new(typedArrayType(options))(array_and_shape.data);
    return torch.Tensor.fromObject({
      data: typed_array,
      shape: array_and_shape.shape,
    });
  }
  if (options === undefined) {
    options = {
      shape: [data.length],
    };
  }
  return torch.Tensor.fromObject({
    data: data,
    ...options,
  });
}

module.exports = torch;