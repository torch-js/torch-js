import * as torch from "../../lib";
import { ScriptModule, rand, tensor } from "../../lib";

test("can run a test module", () => {
  const testModule = new ScriptModule(__dirname + "/test_model.pt");
  expect(testModule).toBeInstanceOf(ScriptModule);

  // Testing rand() with shape array
  const a = rand(1, 5);
  const b = rand([1, 5]);
  const c = testModule.forward(a, b);
});
