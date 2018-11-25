# TorchJS

TorchJS is a JS binding for PyTorch. Its primary objective is to allow running [Torch Script](https://pytorch.org/docs/master/jit.html) inside Node.js program. Complete binding of libtorch is possible but is out-of-scope at the moment.

## Example

In `test/torch_module.py`, you will find the defination of our test module and the code to generate the trace file.

```python
class TestModule(torch.nn.Module):
    def __init__(self):
        super(TestModule, self).__init__()

    def forward(self, input1, input2):
        return input1 + input2
```

Once you have the trace file, you can load it into Node.js like this

```javascript
const torch = require("torch-js");

var test_model_path = "test/test_model.pt";

var script_module = new torch.ScriptModule(test_model_path);
console.log(script_module.toString());

var a = torch.rand(1, 5);
console.log(a.toObject());
var b = torch.rand([1, 5]);
console.log(b.toObject());

var c = script_module.forward(a, b);
console.log(c.toObject());

var d = torch.tensor([[0.1, 0.2, 0.3, 0.4, 0.5]]);
console.log(d.toObject());

var e = script_module.forward(c, d);
console.log(e.toObject());
```

The program above will print something like this on console. Your result will be different from this since `a` and `b` are random variables.

```javascript
ScriptModule("/Users/kittipat/torchjs/tests/test_model.pt")
{ data:
   Float32Array [
     0.5436246991157532,
     0.30234378576278687,
     0.4031236171722412,
     0.8123507499694824,
     0.3121740221977234 ],
  shape: [ 1, 5 ] }
{ data:
   Float32Array [
     0.20072013139724731,
     0.09114563465118408,
     0.588677167892456,
     0.14665216207504272,
     0.8567551374435425 ],
  shape: [ 1, 5 ] }
{ data:
   Float32Array [
     0.7443448305130005,
     0.39348942041397095,
     0.9918007850646973,
     0.9590029120445251,
     1.168929100036621 ],
  shape: [ 1, 5 ] }
{ data:
   Float32Array [
     0.10000000149011612,
     0.20000000298023224,
     0.30000001192092896,
     0.4000000059604645,
     0.5 ],
  shape: [ 1, 5 ] }
{ data:
   Float32Array [
     0.8443448543548584,
     0.593489408493042,
     1.2918007373809814,
     1.359002947807312,
     1.668929100036621 ],
  shape: [ 1, 5 ] }
```

### Tensor creation

There are several ways to create tensors

```javascript
// With TypedArray and shape array
var a = torch.tensor(
  new Float32Array([0.1, 0.2, 0.3, 0.4, 0.5]), {
    shape: [1, 5],
  });

// With array, will create tensor with float32 data type
var b = torch.tensor([
  [0.1, 0.2, 0.3],
  [0.4, 0.5, 0.6],
]);

// With array and option object
var c = torch.tensor([
  [0.1, 0.2, 0.3],
  [0.4, 0.5, 0.6],
], {
  dtype: torch.float64
});

// With torch.Tensor.fromObject()
var d = torch.Tensor.fromObject({
  data: new Float32Array([0.1, 0.2, 0.3, 0.4, 0.5, 0.6]),
  shape: [2, 3],
});
```

## Installation

This project uses `cmake-js` to build Node extension. You will need to download [the preview build of libtorch](https://pytorch.org/get-started/locally/) and extract it to an accessible location. The build script assumes you put `libtorch` in the same directory as this library. E.g., if you checked out this library to `~/torch-js`, then `libtorch` should be at `~/libtorch`. Once you have that, you can run

```bash
yarn install
```

And, to test, run:

```bash
node test/runTorch.js
```

If it failed to run because `libmklml` is missing, you can download it from conda.

```bash
conda install libmklml
```

If conda's `lib` directory is in your path, then you should be able to run the command above. Otherwise, you can set environment variable to point to the directory.

On macOS, it would be:

```bash
DYLD_LIBRARY_PATH=$CONDA_PREFIX/lib/ node tests/runTorch.js
```

On Linux, it should be:

```bash
LD_LIBRARY_PATH=$CONDA_PREFIX/lib/ node tests/runTorch.js
```

If there is any error loading the trace file, you might have to resolve it by installing the matching versions of PyTorch and libtorch and regenerate the file.