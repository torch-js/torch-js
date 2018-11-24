var torch = require("..");

test_model_path = __dirname + "/test_model.pt";

script_module = new torch.ScriptModule(test_model_path);
console.log(script_module.toString());

// Testing rand() with variable number of arguments
a = torch.rand(1, 5);
console.log(a.toObject());
// Testing rand() with shape array
b = torch.rand([1, 5]);
console.log(b.toObject());

c = script_module.forward(a, b);
console.log(c.toObject());

// Testing initialization from object
d = torch.Tensor.fromObject({
  data: new Float32Array([0.1, 0.2, 0.3, 0.4, 0.5]),
  shape: [1, 5],
});
console.log(d.toObject());

e = script_module.forward(c, d);
console.log(e.toObject());

// Testing option parsing
f = torch.rand([1, 5], {dtype: torch.float64});
console.log(f.toObject());
