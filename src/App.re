open Utils;

module Styles = {
  open Css;

  let wrapper =
    style([
      maxHeight(100.0->vh),
      display(flexBox),
      flex(1),
      backgroundColor("091B1D"->hex),
      color(white),
      maxWidth(100.->vw),
    ]);

  let content = style([display(flexBox), flex(1)]);

  let form =
    style([
      flex(1),
      display(flexBox),
      flexDirection(column),
      padding(1.->rem),
    ]);
};

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    <main className=Styles.wrapper>
      <AssetLoader
        images={
          ItemDb.preloadItemIds
          ->Array.slice(~offset=0, ~len=50)
          ->Array.map(Items.ItemImage.make)
          ->Array.map(Items.ItemImage.toString)
        }>
        ...<div className=Styles.content>
             <div className=Styles.form> <ItemCreator /> </div>
           </div>
      </AssetLoader>
    </main>;
  },
};
