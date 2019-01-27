open Items;

let component = ReasonReact.statelessComponent("InventoryItem");

let make = (~item, _children) => {
  ...component,
  render: _self => {
    <div>
      <img src={item.image->ItemImage.toString} alt={item.description} />
    </div>;
  },
};
