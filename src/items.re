open Utils;

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
  let make = string => string;
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

module Rarity = {
  type t =
    | Common
    | Uncommon
    | Rare
    | Epic
    | Legendary;

  let toString = rarity =>
    switch (rarity) {
    | Common => "Common"
    | Uncommon => "Uncommon"
    | Rare => "Rare"
    | Epic => "Epic"
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
  rarity: Rarity.t,
  size: Size.t,
};

let defaultItem = {
  id: ItemId.make("__DEFAULT_ITEM_ID__"),
  name: "__DEFAULT_ITEM__",
  description: "__DEFAULT_ITEM__",
  image: ItemImage.make(""),
  kind: DefaultItem,
  rarity: Common,
  size: (1, 1),
};

let createItem = (~name, ~description, ~image, ~rarity, ~size, ~kind) => {
  id: createItemId(),
  kind,
  name,
  description,
  image,
  rarity,
  size,
};

let createItemFromScratch =
    (~name, ~description, ~image, ~rarity, ~sizeH, ~sizeW, ~kind) => {
  switch (PositiveInt.make(sizeH), PositiveInt.make(sizeW)) {
  | (Some(h), Some(w)) => {
      id: createItemId(),
      name,
      description,
      image,
      rarity,
      size: Size.make(~h, ~w),
      kind,
    }
  | _ => defaultItem
  };
};
