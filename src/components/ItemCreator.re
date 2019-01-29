open Utils;
open Items;

module Styles = {
  open Css;

  let form = style([display(flexBox), flexDirection(column)]);

  let label =
    style([
      display(flexBox),
      flexDirection(column),
      marginBottom(1.0->rem),
    ]);

  let description = style([unsafe("resize", "vertical")]);
};

type state = {items: list(Items.item)};

type actions =
  | AddItem(Items.item)
  | RemoveItem(Items.item);

let component = ReasonReact.reducerComponent("ItemCreator");

let make = _children => {
  ...component,
  initialState: () => {items: []},
  reducer: (action, state) => {
    switch (action) {
    | AddItem(item) =>
      ReasonReact.Update({items: state.items->List.add(item)})
    | RemoveItem(item) =>
      ReasonReact.Update({
        items: state.items->List.keep(i => i.id !== item.id),
      })
    };
  },
  render: self => {
    let handleSubmit = (e, {ReasonReact.send}) => {
      e->ReactEvent.Form.preventDefault;
      let form = e->ReactEvent.Form.target;
      let elements = form##elements;

      let name =
        switch (elements##name##value->Js.Undefined.toOption) {
        | Some(string) => string
        | None => "__DEFAULT_ITEM__"
        };

      let description =
        switch (elements##description##value->Js.Undefined.toOption) {
        | Some(string) => string
        | None => "__DEFAULT_ITEM__"
        };

      let image =
        switch (elements##image##value->Js.Undefined.toOption) {
        | Some(string) => string->ItemImage.make
        | None => ""->ItemImage.make
        };

      let h =
        switch (elements##height##value->int_of_string) {
        | exception _ => 1->PositiveInt.make->Option.getWithDefault(1)
        | x => x->PositiveInt.make->Option.getWithDefault(1)
        };

      let w =
        switch (elements##width##value->int_of_string) {
        | exception _ => 1->PositiveInt.make->Option.getWithDefault(1)
        | x => x->PositiveInt.make->Option.getWithDefault(1)
        };

      let size = Size.make(~h, ~w);

      let rarity =
        switch (elements##rarity##value) {
        | "common" => Rarity.Common
        | "uncommon" => Rarity.Uncommon
        | "rare" => Rarity.Rare
        | "epic" => Rarity.Epic
        | "legendary" => Rarity.Legendary
        | _ => Rarity.Common
        };

      let item =
        createItem(
          ~name,
          ~description,
          ~rarity,
          ~kind=Weapon(OneHanded(Sword)),
          ~size,
          ~image,
        );

      send(AddItem(item));

      form##reset();
    };
    <div>
      <form onSubmit={self.handle(handleSubmit)} className=Styles.form>
        <label className=Styles.label>
          "Name"->text
          <input name="name" id="name" required=true placeholder="Name" />
        </label>
        <label className=Styles.label>
          "Description"->text
          <textarea
            className=Styles.description
            name="description"
            id="description"
            required=true
            placeholder="Description"
          />
        </label>
        <label className=Styles.label>
          "Rarity"->text
          <select name="rarity">
            <option value="common"> "Common"->text </option>
            <option value="uncommon"> "Uncommon"->text </option>
            <option value="rare"> "Rare"->text </option>
            <option value="epic"> "Epic"->text </option>
            <option value="legendary"> "Legendary"->text </option>
          </select>
        </label>
        <label className=Styles.label>
          "Image URL"->text
          <input name="image" id="image" required=true />
        </label>
        <label className=Styles.label>
          "Height"->text
          <input
            name="height"
            id="height"
            required=true
            type_="number"
            min=1
            defaultValue="1"
          />
        </label>
        <label className=Styles.label>
          "Width"->text
          <input
            name="width"
            id="width"
            required=true
            type_="number"
            min=1
            defaultValue="1"
          />
        </label>
        <button> "Create Item"->text </button>
      </form>
      <InventoryList items={self.state.items} />
    </div>;
  },
};
