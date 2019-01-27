open Utils;

type itemId =
  | ItemId(string);

let createItemId = () => Uuid.v4()->ItemId;

type weaponKind =
  | Sword
  | Dagger
  | ShortSword;

type weapon =
  | OneHanded(weaponKind)
  | TwoHanded(weaponKind);

type armor =
  | Chestpiece
  | Boots
  | Legs
  | Helmet
  | Gloves
  | Belt;

type consumable =
  | Food
  | Drink;

type readable =
  | Book
  | Note;

type container =
  | Backpack
  | Box;

type rarity =
  | Common
  | Uncommon
  | Rare
  | Legendary
  | Exotic;

type kind =
  | Weapon(weapon)
  | Armor(armor)
  | Consumable(consumable)
  | Readable(readable)
  | Container(container)
  | DefaultItem;

type item = {
  id: itemId,
  name: string,
  description: string,
  kind,
  rarity,
  size,
};

let defaultItem = {
  id: ItemId("__DEFAULT_ITEM_ID__"),
  name: "__DEFAULT_ITEM__",
  description: "__DEFAULT_ITEM__",
  kind: DefaultItem,
  rarity: Common,
  size: (PositiveInt(1), PositiveInt(1)),
};

let createItem = (~name, ~description, ~rarity, ~size, ~kind) => {
  id: createItemId(),
  kind,
  name,
  description,
  rarity,
  size,
};

let createItemFromScratch =
    (~name, ~description, ~rarity, ~sizeH, ~sizeW, ~kind) => {
  switch (createPositiveInt(sizeH), createPositiveInt(sizeW)) {
  | (Some(h), Some(w)) => {
      id: createItemId(),
      name,
      description,
      rarity,
      size: createSize(~h, ~w),
      kind,
    }
  | _ => defaultItem
  };
};
