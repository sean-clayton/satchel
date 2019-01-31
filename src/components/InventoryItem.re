open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title = rarity =>
    style([color(Colors.rarity(rarity)), fontSize(24->px)]);

  let description = style([]);

  let imageContainer = item => {
    let (h, w) = item.size;

    style([
      height((h * 64)->px),
      width((w * 64)->px),
      display(flexBox),
      justifyContent(center),
      transitionTimingFunction(easeInOut),
      transitionDuration(80),
      transitionProperty("box-shadow, background-color"),
      backgroundColor(Theme.Colors.rarityAlpha(item.rarity, 0.05)),
      backgroundImage(
        linearGradient(
          180->deg,
          [
            (25, Theme.Colors.rarityAlpha(item.rarity, 0.)),
            (100, Theme.Colors.rarityAlpha(item.rarity, 0.1)),
          ],
        ),
      ),
      boxShadows([
        boxShadow(~inset=true, ~spread=1->px, black),
        boxShadow(
          ~inset=true,
          ~spread=2->px,
          Theme.Colors.rarityAlpha(item.rarity, 0.5),
        ),
      ]),
      hover([
        backgroundColor(Theme.Colors.rarityAlpha(item.rarity, 0.15)),
        boxShadows([
          boxShadow(~inset=true, ~spread=1->px, black),
          boxShadow(
            ~inset=true,
            ~spread=2->px,
            Theme.Colors.rarity(item.rarity),
          ),
          boxShadow(
            ~inset=true,
            ~blur=0.5->rem,
            Theme.Colors.rarity(item.rarity),
          ),
          boxShadow(
            ~blur=1.0->rem,
            Theme.Colors.rarityAlpha(item.rarity, 0.25),
          ),
        ]),
      ]),
    ]);
  };

  let image = style([alignSelf(center)]);
};

let component = ReasonReact.statelessComponent("InventoryItem");

let make = (~item, _children) => {
  ...component,
  render: _self => {
    <div>
      <p className={Styles.title(item.rarity)}> item.name->text </p>
      <p> {item.rarity->Rarity.toString->text} </p>
      <p className=Styles.description> <em> item.description->text </em> </p>
      <div className={Styles.imageContainer(item)}>
        <img
          className=Styles.image
          src={item.image->ItemImage.toString}
          alt={item.description}
        />
      </div>
    </div>;
  },
};
