type appAction =
  | RenderAction(RenderStore.renderAction);

type appState = {renderState: RenderStore.renderState};

let appReducer = (state, action) =>
  switch (action) {
  | RenderAction(action) => {
      ...state,
      renderState: RenderStore.renderReduce(state.renderState, action),
    }
  | _ => state
  };

let appStore =
  Reductive.Store.create(
    ~reducer=appReducer,
    ~preloadedState={renderState: RenderStore.createState()},
    (),
  );

include ReductiveContext.Make({
  type state = appState;
  type action = appAction;
});