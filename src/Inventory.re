open Utils;
open Container;
open Items;

let component = ReasonReact.statelessComponent("Inventory");

let make = (~container, _children) => {
  ...component,
  render: _self => {
    <>
      <h1> "Inventory:"->text </h1>
      <ul>
        {container.items
         ->List.toArray
         ->Array.map(({item}) =>
             <li key={item.id->ItemId.toString}>
               <a href={item.image->ItemImage.toString}>
                 {text(item.name)}
               </a>
             </li>
           )
         ->ReasonReact.array}
      </ul>
    </>;
  },
};
