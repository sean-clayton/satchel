open Utils;
open Items;

module Styles = {
  open Css;

  let formWrapper =
    style([flex(1), display(flexBox), flexDirection(column)]);

  let form = style([flex(1), display(flexBox), justifyContent(flexStart)]);

  let formInputs = style([flex(1)]);

  let label =
    style([
      flex(1),
      display(flexBox),
      flexDirection(column),
      marginBottom(1.0->rem),
    ]);

  let imagePickerContainer =
    style([marginLeft(1.->rem), flex(2), overflowY(scroll)]);

  let inventoryContainer = style([flex(1), overflowY(scroll)]);
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
        | exception _ => defaultItem.name
        | Some(string) => string
        | None => Items.defaultItem.name
        };

      let description =
        switch (elements##description##value->Js.Undefined.toOption) {
        | exception _ => defaultItem.description
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
        | "mythical" => Quality.Mythical
        | "legendary" => Quality.Legendary
        | _ => Quality.Common
        };

      let kind =
        switch (elements##kind##value) {
        | "one_handed_sword" => Weapon(OneHanded(Sword))
        | "two_handed_sword" => Weapon(TwoHanded(Sword))
        | "short_sword" => Weapon(OneHanded(ShortSword))
        | "dagger" => Weapon(OneHanded(Dagger))
        | "chestpiece" => Apparel(Chestpiece)
        | "boots" => Apparel(Boots)
        | "helmet" => Apparel(Helmet)
        | "gloves" => Apparel(Gloves)
        | "ring" => Apparel(Ring)
        | "drink" => Consumable(Drink)
        | "book" => Readable(Book)
        | "note" => Readable(Note)
        | "backpack" => Container(Backpack)
        | "box" => Container(Box)
        | _ => DefaultItem
        };

      let item =
        createItem(
          ~name,
          ~description,
          ~quality,
          ~kind,
          ~size,
          ~image=self.state.selectedItemImage,
        );

      send(AddItem(item));
      send(ResetForm);

      form##reset();
    };
    <div className=Styles.formWrapper>
      <form onSubmit={self.handle(handleSubmit)} className=Styles.form>
        <div className=Styles.formInputs>
          <label className=Styles.label>
            "Name"->text
            <input name="name" id="name" required=true placeholder="Name" />
          </label>
          <label className=Styles.label>
            "Description"->text
            <input
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
              <option value="mythical"> "Mythical"->text </option>
              <option value="legendary"> "Legendary"->text </option>
            </select>
          </label>
          <label className=Styles.label>
            "Kind"->text
            <select name="kind">
              <option value="one_handed_sword">
                "One-Handed Sword"->text
              </option>
              <option value="two_handed_sword">
                "Two-Handed Sword"->text
              </option>
              <option value="short_sword"> "Short Sword"->text </option>
              <option value="dagger"> "Dagger"->text </option>
              <option value="chestpiece"> "Chestpiece"->text </option>
              <option value="boots"> "Boots"->text </option>
              <option value="helmet"> "Helmet"->text </option>
              <option value="gloves"> "Gloves"->text </option>
              <option value="ring"> "Ring"->text </option>
              <option value="drink"> "Drink"->text </option>
              <option value="book"> "Book"->text </option>
              <option value="note"> "Note"->text </option>
              <option value="backpack"> "Backpack"->text </option>
              <option value="box"> "Box"->text </option>
            </select>
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
        </div>
        <div className=Styles.imagePickerContainer>
          <label className=Styles.label>
            "Image"->text
            <ItemImagePicker
              onChange=handleNewImage
              value={self.state.selectedItemImage}
              itemImages={ItemDb.preloadItemIds->Array.map(ItemImage.make)}
            />
          </label>
        </div>
        <div className=Styles.inventoryContainer>
          <InventoryList items={self.state.items} />
        </div>
      </form>
    </div>;
  },
};
