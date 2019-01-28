open Utils;
open Container;

module Styles = {
  open Css;

  let wrapper =
    style([
      display(flexBox),
      flex(1),
      padding(1.0->rem),
      backgroundColor(black),
      color(white),
    ]);

  let content =
    style([
      display(grid),
      flex(1),
      unsafe("grid-template-areas", {|
        "inventory form"
      |}),
      gridTemplateColumns([1.0->fr, 1.0->fr]),
    ]);

  let inventory = style([unsafe("grid-area", "inventory")]);

  let form = style([unsafe("grid-area", "form")]);
};

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    let items = [
      (Db.theOneRing, (0, 0)),
      (Db.morgulBlade, (0, 1)),
      (Db.anduril, (2, 0)),
      (Db.sting, (4, 0)),
      (Db.urukHaiChestPiece, (6, 0)),
    ];

    let container =
      items->List.reduce(Db.backpack, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Result.getWithDefault(container)
      );

    let items = container.items;

    <main className=Styles.wrapper>
      <AssetLoader images=Db.preloadImages>
        ...<div className=Styles.content>
             <div className=Styles.inventory>
               <h1> "Inventory:"->text </h1>
               <InventoryList items />
             </div>
             <div className=Styles.form> <ItemCreator /> </div>
           </div>
      </AssetLoader>
    </main>;
  },
};
