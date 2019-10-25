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
        |> Result.bind(DirectorAPIEngine.loopBody)
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
    RenderPst.unsafeGetLoopId(PersistentData.getState())
    |> Result.tap(DomExtend.cancelAnimationFrame)
    |> Result.handleError(Error.throwError);

    DataAPIEngine.unsafeGetState()
    |> Result.bind(state =>
         state
         |> DeviceManagerAPIEngine.unsafeGetGl
         |> Result.tap(DeviceManagerAPIEngine.clear)
       )
    |> Result.handleError(Error.throwError);

    {...state, isStart: false};
  };
};

let renderReduce = (state, action) =>
  switch (action) {
  | Start => Method.start(state)
  | Stop => Method.stop(state)
  };