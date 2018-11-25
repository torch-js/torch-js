// Possible values for dtype
export const float32: number;
export const float64: number;
export const int32: number;

export interface ObjectTensor {
  data: Float32Array|Float64Array|Int32Array;
  shape: number[];
}

export class Tensor {
  static fromObject({data, shape}: ObjectTensor): Tensor;
  toObject(): ObjectTensor;
  toString(): string;
}

export class ScriptModule {
  constructor(path: string);
  forward(...inputs: Tensor[]): Tensor;
  toString(): string;
}

export function rand(shape: number[], options?: {dtype?: number}): Tensor;
// The function actually support options at the end but TS can't express that
export function rand(...shape: number[] /**, options?: {dtype?: number} */):
    Tensor;
