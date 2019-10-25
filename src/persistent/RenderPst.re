open PersistentDataType;

open RenderPstType;

let createData = () => {loopId: None};

let unsafeGetLoopId = state => state.renderData.loopId |> Option.unsafeGet;

let setLoopId = (loopId, state) => {
  ...state,
  renderData: {
    ...state.renderData,
    loopId: Some(loopId),
  },
};