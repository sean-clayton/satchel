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
      (Db.theOneRing, (1, 0)),
      (Db.anduril, (2, 0)),
      (Db.sting, (0, 0)),
    ];

    let initialContainer = createContainerFromScratch(~h=5, ~w=12);

    let container =
      items->List.reduce(initialContainer, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Option.getWithDefault(container)
      );

    <main className=Styles.wrapper>
      <AssetLoader
        sounds=[
          "https://upload.wikimedia.org/wikipedia/commons/c/c8/Example.ogg",
        ]
        images=[
          "https://web.poecdn.com/image/Art/2DItems/Weapons/TwoHandWeapons/TwoHandSwords/TwoHandSword3.png",
          "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/OneHandSwords/OneHandSword4.png",
          "https://web.poecdn.com/image/Art/2DItems/Rings/Ring4.png",
        ]>
        ...<InventoryList container />
      </AssetLoader>
    </main>;
  },
};
