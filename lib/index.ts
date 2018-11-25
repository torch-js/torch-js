'use strict';
import assert = require('assert');
import torch = require('./torch');
export * from './torch';

type Matrix = number[]|NestedArray;
interface NestedArray extends Array<Matrix> {}

function flattenArray(arr: Matrix) {
  let shape = [arr.length];
  while (arr.length > 0 && Array.isArray(arr[0])) {
    shape.push((arr[0] as Matrix).length);
    // Forcing Array<any> is required to make TS happy; otherwise, TS2349
    arr = (arr as Array<any>).reduce((acc, val) => acc.concat(val), []);

    // Running assert in every step to make sure that shape is regular
    const numel = shape.reduce((acc, cur) => acc * cur);
    assert.strictEqual(arr.length, numel);
  }
  return {
    data: (arr as number[]), shape: shape,
  }
}

function typedArrayType(dtype: number) {
  switch (dtype) {
    case torch.float32:
      return Float32Array;
    case torch.float64:
      return Float64Array;
    case torch.int32:
      return Int32Array;
    default:
      throw new TypeError('Unsupported dtype');
  }
}

type TensorDataCompatible = Float32Array|Float64Array|Int32Array|Matrix;

export function tensor(
    data: TensorDataCompatible,
    {dtype = torch.float32, shape}: {dtype?: number, shape?: number[]} = {}) {
  if (Array.isArray(data)) {
    const array_and_shape = flattenArray(data);
    const typed_array = new (typedArrayType(dtype))(array_and_shape.data);
    return torch.Tensor.fromObject({
      data: typed_array,
      shape: array_and_shape.shape,
    });
  }
  if (shape === undefined) {
    shape = [data.length];
  }
  return torch.Tensor.fromObject({
    data: data,
    shape: shape,
  });
}