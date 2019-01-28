open Utils;

type state = {items: list(Items.item)};

type actions =
  | AddItem(Items.item);

let component = ReasonReact.reducerComponent("ItemCreator");

let make = _children => {
  ...component,
  initialState: () => {items: []},
  reducer: (action, state) => {
    switch (action) {
    | AddItem(item) =>
      ReasonReact.Update({items: state.items->List.add(item)})
    };
  },
  render: _self => {
    <div> <form> "I'm a form"->text </form> <ul /> </div>;
  },
};
