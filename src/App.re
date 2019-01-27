open Utils;
open Container;

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    let initialContainer = createContainerFromScratch(~h=5, ~w=12);

    let items = [
      (Database.theOneRing, (NonNegativeInt(1), NonNegativeInt(0))),
      (Database.anduril, (NonNegativeInt(2), NonNegativeInt(0))),
      (Database.sting, (NonNegativeInt(0), NonNegativeInt(0))),
    ];

    let inventory =
      items->List.reduce(initialContainer, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Option.getWithDefault(container)
      );

    let items =
      inventory.items
      ->List.toArray
      ->Array.map(item => {
          let Items.ItemId(id) = item.item.id;
          <li key=id> {text(item.item.name)} </li>;
        });

    <main className={Css.style([Css.flex(1), Css.margin(1.0->Css.rem)])}>
      <h1> "Inventory:"->text </h1>
      <ul> items->ReasonReact.array </ul>
    </main>;
  },
};
