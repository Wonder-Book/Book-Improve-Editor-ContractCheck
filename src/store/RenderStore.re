type renderState = {isStart: bool};

type renderAction =
  | Start
  | Stop;

let createState = () => {isStart: false};

module Method = {
  let start = state => {
    let rec _loop = () =>
      DomExtend.requestAnimationFrame(time => {
        DataAPIEngine.unsafeGetState()
        |> DirectorAPIEngine.loopBody
        |> Result.tap(state => state |> DataAPIEngine.setState)
        |> Result.getSuccessValue(Error.throwError)
        |> ignore;

        _loop();
      })
      |> DomExtend.intToLoopId
      |> RenderPst.setLoopId(_, PersistentData.getState())
      |> PersistentData.setState
      |> ignore;

    _loop();

    {...state, isStart: true};
  };

  let stop = state => {
    DomExtend.cancelAnimationFrame(
      RenderPst.unsafeGetLoopId(PersistentData.getState()),
    );

    {...state, isStart: false};
  };
};

let renderReduce = (state, action) =>
  switch (action) {
  | Start => Method.start(state)
  | Stop => Method.stop(state)
  };