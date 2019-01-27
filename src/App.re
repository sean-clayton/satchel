open Utils;
open Container;
open Items;

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => {
    let initialContainer = createContainerFromScratch(~h=5, ~w=12);

    let items = [
      (Db.theOneRing, (NonNegativeInt(1), NonNegativeInt(0))),
      (Db.anduril, (NonNegativeInt(2), NonNegativeInt(0))),
      (Db.sting, (NonNegativeInt(0), NonNegativeInt(0))),
    ];

    let inventory =
      items->List.reduce(initialContainer, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Option.getWithDefault(container)
      );

    let items =
      inventory.items
      ->List.toArray
      ->Array.map(({item}) =>
          <li key={item.id->ItemId.toString}> {text(item.name)} </li>
        );

    <main className={Css.style([Css.flex(1), Css.margin(1.0->Css.rem)])}>
      <h1> "Inventory:"->text </h1>
      <ul> items->ReasonReact.array </ul>
    </main>;
  },
};
