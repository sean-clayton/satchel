open Utils;
open Container;

module Styles = {
  open Css;

  let wrapper =
    style([
      flex(1),
      padding(1.0->rem),
      backgroundColor(black),
      color(white),
    ]);
};

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    let items = [
      (Db.theOneRing, (0, 0)),
      (Db.morgulBlade, (0, 1)),
      (Db.anduril, (2, 0)),
      (Db.sting, (1, 0)),
    ];

    let container =
      items->List.reduce(Db.backpack, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Result.getWithDefault(container)
      );

    <main className=Styles.wrapper>
      <AssetLoader
        images=[
          "https://web.poecdn.com/image/Art/2DItems/Weapons/TwoHandWeapons/TwoHandSwords/TwoHandSword3.png",
          "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/OneHandSwords/OneHandSword4.png",
          "https://web.poecdn.com/image/Art/2DItems/Rings/Ring4.png",
          "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/Daggers/Dagger8.png",
        ]>
        ...<InventoryList container />
      </AssetLoader>
    </main>;
  },
};
