open Utils;
open Container;
open Items;

module Styles = {
  open Css;

  let wrapper = style([listStyleType(none), margin(zero), padding(zero)]);
};

let component = ReasonReact.statelessComponent("InventoryList");

let make = (~container, _children) => {
  ...component,
  render: _self => {
    <div>
      <h1> "Inventory:"->text </h1>
      <ul className=Styles.wrapper>
        {container.items
         ->List.toArray
         ->Array.map(({item}) =>
             <li key={item.id->ItemId.toString}> <InventoryItem item /> </li>
           )
         ->ReasonReact.array}
      </ul>
    </div>;
  },
};
