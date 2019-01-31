open Utils;

module Styles = {
  open Css;

  let imageWrapper =
    style([
      display(inlineFlex),
      justifyContent(center),
      alignItems(center),
      position(relative),
      height(128->px),
      width(128->px),
    ]);

  let selectedImage = style([backgroundColor(rgba(0, 75, 255, 0.666))]);

  let image = style([position(absolute)]);
};

let component = ReasonReact.statelessComponent("ItemImagePicker");

let make =
    (
      ~itemImages: list(Items.ItemImage.t),
      ~value=itemImages->List.head,
      ~onChange,
      _children,
    ) => {
  ...component,
  render: _self => {
    let handleSelectItem = onChange;
    let value = value->Option.getWithDefault(Items.defaultItem.image);

    <div>
      {itemImages
       ->List.toArray
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
