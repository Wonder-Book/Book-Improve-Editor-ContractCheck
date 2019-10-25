type loopId;

external intToLoopId: int => loopId = "%identity";

let requestAnimationFrame = TinyWonderEngine.DomExtend.requestAnimationFrame;

[@bs.val] external cancelAnimationFrame: loopId => unit = "";