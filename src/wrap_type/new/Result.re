include TinyWonderEngine.Result;

let map = (oneTrackFunc, twoTrackInput) =>
  either(result => result |> oneTrackFunc |> succeed, fail, twoTrackInput);