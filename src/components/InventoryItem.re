open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title =
    style([
      fontSize(24->px),
      textShadow(~x=zero, ~y=2->px, ~blur=4->px, rgba(0, 0, 0, 0.75)),
    ]);

  let description = style([]);

  let image = rarity =>
    style([padding(13->px), backgroundColor(Colors.rarity(rarity))]);
};

let component = ReasonReact.statelessComponent("InventoryItem");

let make = (~item, _children) => {
  ...component,
  render: _self => {
    <div>
      <p className=Styles.title> item.name->text </p>
      <p> {item.rarity->Rarity.toString->text} </p>
      <p className=Styles.description> <em> item.description->text </em> </p>
      <img
        className={Styles.image(item.rarity)}
        src={item.image->ItemImage.toString}
        alt={item.description}
      />
    </div>;
  },
};
