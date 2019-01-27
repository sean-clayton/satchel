open Utils;
open Container;

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

    let container =
      items->List.reduce(initialContainer, (container, (item, coords)) =>
        tryToAddItemToContainer(~item, ~container, ~coords)
        ->Option.getWithDefault(container)
      );

    <main className={Css.style([Css.flex(1), Css.margin(1.0->Css.rem)])}>
      <Inventory container />
    </main>;
  },
};
