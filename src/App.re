let component = ReasonReact.statelessComponent("App");

let make = _ => {
  ...component,
  render: _self => <main> <h1> {ReasonReact.string("Howdy!")} </h1> </main>,
};
