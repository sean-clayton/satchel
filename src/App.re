open Utils;
open Container;

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

  let content =
    style([
      display(grid),
      flex(1),
      unsafe("grid-template-areas", {|
        "inventory form"
      |}),
      gridTemplateColumns([1.0->fr, 2.0->fr]),
      gridTemplateRows([100.->vh]),
    ]);

  let inventoryContainer =
    style([
      unsafe("grid-area", "inventory"),
      display(flexBox),
      flexDirection(column),
      backgroundColor(rgba(0, 0, 0, 0.25)),
      height(100.->vh),
    ]);

  let inventoryTitle = style([padding(1.->rem)]);

  let inventory = style([flex(1), overflowY(scroll), padding(1.->rem)]);

  let form =
    style([
      unsafe("grid-area", "form"),
      display(flexBox),
      flexDirection(column),
      padding(1.->rem),
    ]);
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
          ItemDb.preloadItemIds
          ->Array.slice(~offset=0, ~len=50)
          ->Array.map(Items.ItemImage.make)
          ->Array.map(Items.ItemImage.toString)
        }>
        ...<div className=Styles.content>
             <div className=Styles.inventoryContainer>
               <h1 className=Styles.inventoryTitle> "Inventory:"->text </h1>
               <div className=Styles.inventory> <InventoryList items /> </div>
             </div>
             <div className=Styles.form> <ItemCreator /> </div>
           </div>
      </AssetLoader>
    </main>;
  },
};
