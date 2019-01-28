open Utils;
open Items;

module Styles = {
  open Css;

  let wrapper = style([listStyleType(none), margin(zero), padding(zero)]);
};

let component = ReasonReact.statelessComponent("InventoryList");

let make = (~items, _children) => {
  ...component,
  render: _self => {
    <ul className=Styles.wrapper>
      {items
       ->List.toArray
       ->Array.map(item =>
           <li key={item.id->ItemId.toString}> <InventoryItem item /> </li>
         )
       ->ReasonReact.array}
    </ul>;
  },
};
