open PersistentDataType;

let _createState = () => {renderData: RenderPst.createData()};

let stateData = {state: _createState()};

let getStateData = () => stateData;

let getState = () => getStateData().state;

let setState = state => {
  getStateData().state = state;

  state;
};