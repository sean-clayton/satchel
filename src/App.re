open Utils;
open Container;

let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  didMount: _self => {
    let container =
      tryToAddItemToContainer(
        ~item=Database.sting,
        ~container=createContainerFromScratch(~h=5, ~w=5),
        ~coords=(NonNegativeInt(0), NonNegativeInt(0)),
      )
      ->Option.getWithDefault(defaultContainer);

    canAddItemToContainerAtCoords(
      ~item=Database.anduril,
      ~container,
      ~coords=(NonNegativeInt(0), NonNegativeInt(0)),
    )
    ->Js.log;
  },
  render: _self => <main> <h1> {ReasonReact.string("Howdy!")} </h1> </main>,
};
