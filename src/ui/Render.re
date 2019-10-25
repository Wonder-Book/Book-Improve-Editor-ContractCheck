let renderSelector = (uiState: AppStore.appState) => uiState.renderState;

module Method = {
  let _createCameraData = canvas => (
    MatrixWTEngine.createIdentityMatrix()
    |> MatrixWTEngine.setLookAt(
         VectorWTEngine.create(0., 0.0, 5.),
         VectorWTEngine.create(0., 0., -100.),
         VectorWTEngine.create(0., 1., 0.),
       )
    |> CoordinateTransformationMatrixWTEngine.View.create,
    MatrixWTEngine.createIdentityMatrix()
    |> MatrixWTEngine.buildPerspective((
         CameraWTEngine.Frustum.Fovy.create(30.),
         CameraWTEngine.Frustum.Aspect.create(
           (canvas##width |> Js.Int.toFloat)
           /. (canvas##height |> Js.Int.toFloat),
         ),
         CameraWTEngine.Frustum.Near.create(1.),
         CameraWTEngine.Frustum.Far.create(100.),
       ))
    |> Result.map(mat =>
         mat |> CoordinateTransformationMatrixWTEngine.Projection.create
       ),
  );

  let initEngine = () => {
    let state =
      DataAPIEngine.createState() |> ViewAPIEngine.setCanvasById("webgl");

    let canvas = ViewAPIEngine.unsafeGetCanvas(state);

    let state =
      state
      |> DeviceManagerAPIEngine.setClearColor(
           ColorWTEngine.Color4.create(0., 0., 0., 1.),
         )
      |> ShaderAPIEngine.addGLSL(
           ShaderNameWTEngine.create("shader1"),
           (
             GLSLWTEngine.VS.create(GLSL.vs1),
             GLSLWTEngine.FS.create(GLSL.fs1),
           ),
         )
      |> ShaderAPIEngine.addGLSL(
           ShaderNameWTEngine.create("shader2"),
           (
             GLSLWTEngine.VS.create(GLSL.vs2),
             GLSLWTEngine.FS.create(GLSL.fs2),
           ),
         )
      |> GameObjectAPIEngine.addGameObjectData(
           MatrixWTEngine.createIdentityMatrix()
           |> MatrixWTEngine.setTranslation(
                VectorWTEngine.create(0.75, 0., 0.),
              )
           |> CoordinateTransformationMatrixWTEngine.Model.create,
           GameObjectAPIEngine.createTriangleGeometryData(),
           (
             ShaderNameWTEngine.create("shader1"),
             [ColorWTEngine.Color3.create(1., 0., 0.)],
           ),
         )
      |> GameObjectAPIEngine.addGameObjectData(
           MatrixWTEngine.createIdentityMatrix()
           |> MatrixWTEngine.setTranslation(
                VectorWTEngine.create(0., 0., 0.5),
              )
           |> CoordinateTransformationMatrixWTEngine.Model.create,
           GameObjectAPIEngine.createTriangleGeometryData(),
           (
             ShaderNameWTEngine.create("shader2"),
             [
               ColorWTEngine.Color3.create(0., 0.8, 0.),
               ColorWTEngine.Color3.create(0., 0.5, 0.),
             ],
           ),
         )
      |> GameObjectAPIEngine.addGameObjectData(
           MatrixWTEngine.createIdentityMatrix()
           |> MatrixWTEngine.setTranslation(
                VectorWTEngine.create(-0.5, 0., -2.),
              )
           |> CoordinateTransformationMatrixWTEngine.Model.create,
           GameObjectAPIEngine.createTriangleGeometryData(),
           (
             ShaderNameWTEngine.create("shader1"),
             [ColorWTEngine.Color3.create(0., 0., 1.)],
           ),
         );

    let (vMatrix, pMatrixResult) = _createCameraData(canvas);

    pMatrixResult
    |> Result.map(pMatrix =>
         state |> CameraAPIEngine.setCameraData((vMatrix, pMatrix))
       )
    |> Result.bind(state =>
         state
         |> DirectorAPIEngine.initAll(
              {
                "alpha": true,
                "depth": true,
                "stencil": false,
                "antialias": true,
                "premultipliedAlpha": true,
                "preserveDrawingBuffer": false,
              }: Gl.contextConfigJsObj,
            )
       )
    |> Result.map(DataAPIEngine.setState);
  };
};

[@react.component]
let make = () => {
  let dispatch = AppStore.useDispatch();
  let uiState = AppStore.useSelector(renderSelector);

  React.useEffect1(
    () => {
      Method.initEngine()
      |> Result.getSuccessValue(Error.throwError)
      |> ignore;

      None;
    },
    [||],
  );

  <article>
    <canvas key="canvas" id="webgl" width="400" height="400">
      {ReasonReact.string({|Please use a browser that supports "canvas"|})}
    </canvas>
    {
      uiState.isStart ?
        <button
          onClick={_ => dispatch(AppStore.RenderAction(RenderStore.Stop))}>
          {ReasonReact.string("Stop")}
        </button> :
        <button
          onClick={_ => dispatch(AppStore.RenderAction(RenderStore.Start))}>
          {ReasonReact.string("Start")}
        </button>
    }
  </article>;
};