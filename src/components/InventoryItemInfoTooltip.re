open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title = quality =>
    style([color(Colors.quality(quality)), fontSize(24->px)]);

  let description = style([]);

  let wrapper =
    style([position(absolute), backgroundColor(black), padding(1.->rem)]);
};

let component = ReasonReact.statelessComponent("InventoryItemInfoTooltip");

let make = (~item, ~x=0, ~y=0, _children) => {
  ...component,
  render: _self => {
    let style =
      ReactDOMRe.Style.make(
        ~top=y->string_of_int,
        ~left=x->string_of_int,
        (),
      );
    let qualityS = item.quality->Quality.toString;
    let kindS = item.kind->kindToString;

    <div style className=Styles.wrapper>
      <p className={Styles.title(item.quality)}> item.name->text </p>
      <p> {j|$qualityS $kindS|j}->text </p>
      <p className=Styles.description> <em> item.description->text </em> </p>
    </div>;
  },
};
