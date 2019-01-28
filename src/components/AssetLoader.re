open Utils;

module Styles = {
  open Css;

  let wrapper =
    style([
      position(fixed),
      top(zero),
      left(zero),
      right(zero),
      bottom(zero),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
    ]);

  let hiddenAsset = style([display(none)]);

  let loaderWrapper =
    style([
      position(relative),
      display(flexBox),
      justifyContent(center),
      alignItems(center),
      height(1.5->rem),
      width(30.0->vw),
      fontWeight(bold),
      textShadow(~y=1->px, ~blur=2->px, rgba(0, 0, 0, 0.5)),
      borderRadius(9999->px),
      backgroundColor(rgba(255, 255, 255, 0.1)),
      zIndex(1),
      cursor(`default),
    ]);

  let loaderText = style([zIndex(1)]);

  let loader =
    style([
      position(absolute),
      height(100.0->pct),
      width(100.0->pct),
      left(zero),
      backgroundColor("07f"->hex),
      boxShadow(~inset=true, ~y=1->px, rgba(255, 255, 255, 0.5)),
      borderRadius(9999->px),
    ]);
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

    let progressf =
      self.state.numLoaded->float_of_int /. numTotalAssets->float_of_int;

    let progress = progressf *. 100.0;

    let progressStyle =
      ReactDOMRe.Style.make(~width=progress->Js.Float.toString ++ "%", ());

    switch (self.state.numLoaded === numTotalAssets) {
    | true => children
    | _ =>
      <div className=Styles.wrapper>
        <div className=Styles.loaderWrapper>
          <span className=Styles.loaderText>
            {(progress->Js.Float.toFixed ++ "%")->text}
          </span>
          <span style=progressStyle className=Styles.loader />
        </div>
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
      </div>
    };
  },
};
