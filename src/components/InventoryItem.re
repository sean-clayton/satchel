open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title = rarity =>
    style([color(Colors.rarity(rarity)), fontSize(24->px)]);

  let description = style([]);

  let image = rarity =>
    style([
      boxShadow(
        ~inset=true,
        ~x=zero,
        ~y=zero,
        ~spread=3->px,
        Colors.rarity(rarity),
      ),
      padding(13->px),
    ]);
};

let component = ReasonReact.statelessComponent("InventoryItem");

let make = (~item, _children) => {
  ...component,
  render: _self => {
    <div>
      <p className={Styles.title(item.rarity)}> item.name->text </p>
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
