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

  let form = style([flex(1), display(flexBox), flexDirection(column)]);
};

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    let itemIds =
      switch (Environment.nodeEnv) {
      | "production" => ItemIds.all
      | _ => ItemIds.all->Array.slice(~offset=0, ~len=50)
      };
    <main className=Styles.wrapper>
      <AssetLoader
        images={
          itemIds
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
