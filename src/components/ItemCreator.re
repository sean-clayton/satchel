open Utils;
open Items;

module Styles = {
  open Css;

  let form = style([display(flexBox), flexDirection(column)]);

  let label =
    style([
      flex(1),
      display(flexBox),
      flexDirection(column),
      marginBottom(1.0->rem),
    ]);

  let description = style([unsafe("resize", "vertical")]);

  let imagePickerContainer =
    style([maxHeight((128 * 4)->px), overflowY(scroll)]);
};

type state = {
  items: list(Items.item),
  selectedItemImage: Items.ItemImage.t,
};

type actions =
  | AddItem(Items.item)
  | RemoveItem(Items.item)
  | SelectItemImage(Items.ItemImage.t)
  | ResetForm;

let component = ReasonReact.reducerComponent("ItemCreator");

let make = _children => {
  ...component,
  initialState: () => {items: [], selectedItemImage: defaultItem.image},
  reducer: (action, state) => {
    switch (action) {
    | AddItem(item) =>
      ReasonReact.Update({...state, items: state.items->List.add(item)})
    | RemoveItem(item) =>
      ReasonReact.Update({
        ...state,
        items: state.items->List.keep(i => i.id !== item.id),
      })
    | SelectItemImage(image) =>
      ReasonReact.Update({...state, selectedItemImage: image})
    | ResetForm =>
      ReasonReact.Update({...state, selectedItemImage: defaultItem.image})
    };
  },
  render: self => {
    let handleNewImage = image => self.send(SelectItemImage(image));
    let handleSubmit = (e, {ReasonReact.send}) => {
      e->ReactEvent.Form.preventDefault;
      let form = e->ReactEvent.Form.target;
      let elements = form##elements;

      let name =
        switch (elements##name##value->Js.Undefined.toOption) {
        | Some(string) => string
        | None => Items.defaultItem.name
        };

      let description =
        switch (elements##description##value->Js.Undefined.toOption) {
        | Some(string) => string
        | None => Items.defaultItem.description
        };

      let (dH, dW) = Items.defaultItem.size;

      let size =
        switch (
          elements##height##value->int_of_string,
          elements##width##value->int_of_string,
        ) {
        | exception _ => Items.defaultItem.size
        | (h, w) => (
            h->PositiveInt.make->Option.getWithDefault(dH),
            w->PositiveInt.make->Option.getWithDefault(dW),
          )
        };

      let quality =
        switch (elements##quality##value) {
        | "common" => Quality.Common
        | "uncommon" => Quality.Uncommon
        | "rare" => Quality.Rare
        | "legendary" => Quality.Legendary
        | "mythical" => Quality.Mythical
        | _ => Quality.Common
        };

      let item =
        createItem(
          ~name,
          ~description,
          ~quality,
          ~kind=Weapon(OneHanded(Sword)),
          ~size,
          ~image=self.state.selectedItemImage,
        );

      send(AddItem(item));
      send(ResetForm);

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
          "Quality"->text
          <select name="quality">
            <option value="common"> "Common"->text </option>
            <option value="uncommon"> "Uncommon"->text </option>
            <option value="rare"> "Rare"->text </option>
            <option value="legendary"> "Legendary"->text </option>
            <option value="mythical"> "Mythical"->text </option>
          </select>
        </label>
        <label className=Styles.label>
          "Image"->text
          <div className=Styles.imagePickerContainer>
            <ItemImagePicker
              onChange=handleNewImage
              value={Some(self.state.selectedItemImage)}
              itemImages={Items.preloadImages->List.map(ItemImage.make)}
            />
          </div>
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
