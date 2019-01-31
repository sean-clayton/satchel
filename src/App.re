open Utils;
open Container;

module Styles = {
  open Css;

  let wrapper =
    style([
      display(flexBox),
      flex(1),
      padding(1.0->rem),
      backgroundImage(url("/assets/bg-repeat.jpg")),
      backgroundAttachment(fixed),
      unsafe("background-position", "center center"),
      unsafe("background-repeat", "repeat-y"),
      backgroundColor("091B1D"->hex),
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
    let container =
      ItemDb.predefinedItems
      ->List.zip([(0, 0), (0, 1), (0, 3), (1, 0), (1, 2), (2, 0)])
      ->List.reduce(ItemDb.backpack, (container, (item, coords)) =>
          tryToAddItemToContainer(~item, ~container, ~coords)
          ->Result.getWithDefault(container)
        );

    let items = container.items->List.map(i => i.item);

    <main className=Styles.wrapper>
      <AssetLoader
        images={
          Items.preloadImages
          ->List.map(Items.ItemImage.make)
          ->List.map(Items.ItemImage.toString)
        }>
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
