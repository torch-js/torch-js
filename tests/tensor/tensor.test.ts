import * as torch from "../../lib";
import { rand, tensor, Tensor } from "../../lib";

test("can create a tensor from a Float32Array", () => {
  // Testing initialization from object
  const d = tensor(new Float32Array([0.1, 0.2, 0.3, 0.4, 0.5]), {
    shape: [1, 5]
  });
});

test("create Float32 tensor from nested array", () => {
  const x = tensor([[0.1, 0.2, 0.3], [0.4, 0.5, 0.6]]);
  expect(x).toBeInstanceOf(Tensor);
  expect(x.toObject().data).toBeInstanceOf(Float32Array);
  expect(x.toObject().shape).toEqual([2, 3]);
});

test("create Float64 tensor from nested array", () => {
  const x = tensor([[0.1, 0.2, 0.3], [0.4, 0.5, 0.6]], {
    dtype: torch.float64
  });
  expect(x).toBeInstanceOf(Tensor);
  expect(x.toObject().data).toBeInstanceOf(Float64Array);
  expect(x.toObject().shape).toEqual([2, 3]);
});
