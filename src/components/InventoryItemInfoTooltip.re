open Utils;
open Items;

module Styles = {
  open Css;
  open Theme;

  let title = quality =>
    style([color(Colors.quality(quality)), fontSize(24->px)]);

  let description = style([]);

  let wrapper =
    style([
      pointerEvents(none),
      position(absolute),
      backgroundColor(black),
      padding(1.->rem),
      top(0->px),
      left(0->px),
    ]);
};

let component = ReasonReact.statelessComponent("InventoryItemInfoTooltip");

/**
  In order dynamically position the tooltip relative to the screen borders and mouse,
  we need to capture the the following things in didMount:

  - Element height/width
  - Screen height/width (Maybe do observer on screen dimensions if screen is resized?)

  We already have x and y of the mouse from props and we can just
  recalculate everything in render
 */

let make = (~item, ~x, ~y, _children) => {
  ...component,
  render: _self => {
    let xS = y->string_of_int ++ "px";
    let yS = x->string_of_int ++ "px";
    let style =
      ReactDOMRe.Style.make(~transform={j|translate($yS, $xS)|j}, ());
    let qualityS = item.quality->Quality.toString;
    let kindS = item.kind->kindToString;

    <div style className=Styles.wrapper>
      <p className={Styles.title(item.quality)}> item.name->text </p>
      <p> {j|$qualityS $kindS|j}->text </p>
      <p className=Styles.description> <em> item.description->text </em> </p>
    </div>;
  },
};
