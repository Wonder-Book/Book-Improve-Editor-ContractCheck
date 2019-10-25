/* let contentSelector = (state: AppStore.appState) => state.content;

   module StringComponent = {
     [@react.component]
     let make = () => {
       Js.logMany([|"content" |> Obj.magic|]);
       let dispatch = AppStore.useDispatch();
       let state = AppStore.useSelector(contentSelector);

       <div>
         <div> {ReasonReact.string("Content: " ++ state)} </div>
         <button onClick={_ => dispatch(StringAction(AppendA))}>
           {ReasonReact.string("+A")}
         </button>
         <button onClick={_ => dispatch(StringAction(AppendB))}>
           {ReasonReact.string("+B")}
         </button>
       </div>;
     };
   }; */

/* let renderSelector = (state: AppStore.appState) => state.renderState;

   module CounterComponent = {
     [@react.component]
     let make = () => {
       /* Js.logMany([|"counter" |> Obj.magic|]); */
       let dispatch = AppStore.useDispatch();
       let state = AppStore.useSelector(renderSelector);

       <div>
         <div> {ReasonReact.string("Counter: " ++ string_of_int(state))} </div>
         <button onClick={_ => dispatch(CounterAction(Increment))}>
           {ReasonReact.string("++")}
         </button>
         <button onClick={_ => dispatch(CounterAction(Decrement))}>
           {ReasonReact.string("--")}
         </button>
       </div>;
     };
   }; */

[@react.component]
let make = () => <div> <Render /> </div>;