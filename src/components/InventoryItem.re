open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title = quality =>
    style([color(Colors.quality(quality)), fontSize(24->px)]);

  let description = style([]);

  let imageContainerBase =
    style([
      display(flexBox),
      justifyContent(center),
      transitionTimingFunction(easeInOut),
      transitionDuration(80),
      transitionProperty("box-shadow, background-color"),
    ]);

  let imageContainer = item => {
    let (h, w) = item.size;
    let (o1, o2, o3, o4, o5, pct1) =
      switch (item.quality) {
      | Legendary
      | Mythical => (0.5, 0.15, 0.25, 0.5, 0.5, 50)
      | _ => (0.1, 0.05, 0., 0.15, 0.25, 25)
      };

    style([
      height((h * 64)->px),
      width((w * 64)->px),
      backgroundColor(Theme.Colors.qualityAlpha(item.quality, o2)),
      backgroundImage(
        linearGradient(
          180->deg,
          [
            (pct1, Theme.Colors.qualityAlpha(item.quality, o3)),
            (100, Theme.Colors.qualityAlpha(item.quality, o1)),
          ],
        ),
      ),
      boxShadows([
        boxShadow(~inset=true, ~spread=1->px, black),
        boxShadow(
          ~inset=true,
          ~spread=2->px,
          Theme.Colors.qualityAlpha(item.quality, 0.5),
        ),
      ]),
      hover([
        backgroundColor(Theme.Colors.qualityAlpha(item.quality, o4)),
        boxShadows([
          boxShadow(~inset=true, ~spread=1->px, black),
          boxShadow(
            ~inset=true,
            ~spread=2->px,
            Theme.Colors.quality(item.quality),
          ),
          boxShadow(
            ~inset=true,
            ~blur=0.5->rem,
            Theme.Colors.quality(item.quality),
          ),
          boxShadow(
            ~blur=1.0->rem,
            Theme.Colors.qualityAlpha(item.quality, o5),
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
      <p className={Styles.title(item.quality)}> item.name->text </p>
      <p> {item.quality->Quality.toString->text} </p>
      <p className=Styles.description> <em> item.description->text </em> </p>
      <div
        className=Styles.(
          Css.merge([imageContainerBase, imageContainer(item)])
        )>
        <img
          className=Styles.image
          src={item.image->ItemImage.toString}
          alt={item.description}
        />
      </div>
    </div>;
  },
};
