open Utils;

let preloadItemIds: array(string) = [%bs.raw {|require('./ids.json')|}];

module ItemId: {
  type t;
  let make: string => t;
  let toString: t => string;
} = {
  type t = string;
  let make = string => string;
  let toString = t => t;
};

let createItemId = () => Uuid.v4()->ItemId.make;

module ItemImage: {
  type t;
  let make: string => t;
  let toString: t => string;
} = {
  type t = string;
  let make = string =>
    Environment.imageHost
    ++ "/images/d3/icons/items/large/"
    ++ string
    ++ ".png";
  let toString = t => t;
};

type weaponKind =
  | Sword
  | Dagger
  | ShortSword;

type weapon =
  | OneHanded(weaponKind)
  | TwoHanded(weaponKind);

type apparel =
  | Chestpiece
  | Boots
  | Legs
  | Helmet
  | Gloves
  | Belt
  | Ring;

type consumable =
  | Food
  | Drink;

type readable =
  | Book
  | Note;

type container =
  | Backpack
  | Box;

module Quality = {
  type t =
    | Common
    | Uncommon
    | Rare
    | Mythical
    | Legendary;

  let toString = quality =>
    switch (quality) {
    | Common => "Common"
    | Uncommon => "Uncommon"
    | Rare => "Rare"
    | Mythical => "Mythical"
    | Legendary => "Legendary"
    };
};

type kind =
  | Weapon(weapon)
  | Apparel(apparel)
  | Consumable(consumable)
  | Readable(readable)
  | Container(container)
  | DefaultItem;

type item = {
  id: ItemId.t,
  name: string,
  description: string,
  image: ItemImage.t,
  kind,
  quality: Quality.t,
  size: Size.t,
};

let defaultItem = {
  id: ItemId.make("__DEFAULT_ITEM_ID__"),
  name: "__DEFAULT_ITEM__",
  description: "__DEFAULT_ITEM__",
  image:
    ItemImage.make(
      preloadItemIds[0]
      ->Option.getWithDefault("primordialkey_demonhunter_male"),
    ),
  kind: DefaultItem,
  quality: Common,
  size: (1, 1),
};

let createItem = (~name, ~description, ~image, ~quality, ~size, ~kind) => {
  id: createItemId(),
  kind,
  name,
  description,
  image,
  quality,
  size,
};

let createItemFromScratch =
    (~name, ~description, ~image, ~quality, ~sizeH, ~sizeW, ~kind) => {
  switch (PositiveInt.make(sizeH), PositiveInt.make(sizeW)) {
  | (Some(h), Some(w)) => {
      id: createItemId(),
      name,
      description,
      image,
      quality,
      size: Size.make(~h, ~w),
      kind,
    }
  | _ => defaultItem
  };
};
