open Utils;
open Items;

module Styles = {
  open Css;

  let wrapper =
    style([
      display(grid),
      listStyleType(none),
      margin(zero),
      unsafe("grid-template-columns", "repeat(auto-fit, 64px)"),
      padding(1.->rem),
    ]);
};

let component = ReasonReact.statelessComponent("InventoryList");

let make = (~items, _children) => {
  ...component,
  render: _self => {
    <div className=Styles.wrapper>
      {items
       ->List.toArray
       ->Array.map(item =>
           <InventoryItem item key={item.id->ItemId.toString} />
         )
       ->ReasonReact.array}
    </div>;
  },
};
