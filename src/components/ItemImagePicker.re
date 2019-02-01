open Utils;

module Styles = {
  open Css;

  let container =
    style([
      display(grid),
      unsafe("grid-template-columns", "repeat(auto-fit, minmax(128px, 1fr))"),
      unsafe("grid-auto-rows", "128px"),
    ]);

  let imageWrapper =
    style([
      display(flexBox),
      justifyContent(center),
      alignItems(center),
      position(relative),
    ]);

  let selectedImage = style([backgroundColor(rgba(0, 75, 255, 0.666))]);

  let image = style([position(absolute)]);
};

let component = ReasonReact.statelessComponent("ItemImagePicker");

let make =
    (
      ~itemImages: array(Items.ItemImage.t),
      ~value: Items.ItemImage.t,
      ~onChange,
      _children,
    ) => {
  ...component,
  render: _self => {
    let handleSelectItem = onChange;

    <div className=Styles.container>
      {itemImages
       ->Array.map(itemImage => {
           let activeClass =
             switch (value == itemImage) {
             | true => Styles.selectedImage
             | _ => ""
             };

           <div
             key={itemImage->Items.ItemImage.toString}
             onClick={_ => handleSelectItem(itemImage)}
             className=Styles.(Css.merge([imageWrapper, activeClass]))>
             <img
               className=Styles.image
               src={itemImage->Items.ItemImage.toString}
             />
           </div>;
         })
       ->ReasonReact.array}
    </div>;
  },
};
