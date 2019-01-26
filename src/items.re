open Utils;

type itemId =
  | ItemId(string);

let createItemId = () => Uuid.v4()->ItemId;

type weaponKind =
  | Sword
  | Dagger;

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
  | Container(container);

type item = {
  id: itemId,
  name: string,
  description: string,
  kind,
  rarity,
  size,
};

let createItem = (~name, ~description, ~rarity, ~size, ~kind) => {
  id: createItemId(),
  kind,
  name,
  description,
  rarity,
  size,
};
