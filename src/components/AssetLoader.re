open Utils;

module Styles = {
  open Css;

  let hiddenAsset = style([display(none)]);
};

type state = {numLoaded: int};

type actions =
  | LoadedAsset;

let component = ReasonReact.reducerComponent("ImageLoader");

let make = (~images=[], ~sounds=[], children) => {
  ...component,
  initialState: () => {numLoaded: 0},
  reducer: (action, state) => {
    switch (action) {
    | LoadedAsset => ReasonReact.Update({numLoaded: state.numLoaded + 1})
    };
  },
  shouldUpdate: ({oldSelf, newSelf}) => {
    switch (oldSelf, newSelf) {
    | ({state: {numLoaded: old}}, {state: {numLoaded: new_}}) =>
      old !== new_
    };
  },
  render: self => {
    let onLoad = _ => self.send(LoadedAsset);
    let numTotalAssets = List.concat(images, sounds)->List.length;

    switch (self.state.numLoaded === numTotalAssets) {
    | true => children
    | _ =>
      <>
        {sounds
         ->List.toArray
         ->Array.map(sound =>
             <audio key=sound src=sound onCanPlayThrough=onLoad />
           )
         ->ReasonReact.array}
        {images
         ->List.toArray
         ->Array.map(image =>
             <img className=Styles.hiddenAsset key=image src=image onLoad />
           )
         ->ReasonReact.array}
      </>
    };
  },
};
