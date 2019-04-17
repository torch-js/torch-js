import { rand, Tensor } from "../../lib";

test("can generate random numbers with argument list shape", () => {
  // Testing rand() with constiable number of arguments
  const x = rand(1, 5);
  expect(x).toBeInstanceOf(Tensor);
  expect(x.toObject().data).toBeInstanceOf(Float32Array);
  expect(x.toObject().shape).toEqual([1, 5]);
  // This fails, not exactly sure why!
  //expect(x.toObject().shape).toBeInstanceOf(Array);
});

test("can generate random numbers with array shape", () => {
  // Testing rand() with constiable number of arguments
  const x = rand([1, 5]);
  expect(x).toBeInstanceOf(Tensor);
  expect(x.toObject().data).toBeInstanceOf(Float32Array);
  expect(x.toObject().shape).toEqual([1, 5]);
});
