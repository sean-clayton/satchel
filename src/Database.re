open Utils;
open Items;

let anduril = {
  id: createItemId(),
  name: "Andúril",
  description: "A longsword reforged from the shards of Narsil.",
  rarity: Legendary,
  kind: Weapon(TwoHanded(Sword)),
  size: (PositiveInt(4), PositiveInt(2)),
};

let sting = {
  id: createItemId(),
  name: "Sting",
  description: "A short sword that glows when orcs or goblins are nearby.",
  rarity: Exotic,
  kind: Weapon(OneHanded(ShortSword)),
  size: (PositiveInt(2), PositiveInt(1)),
};

let predefinedItems = [sting, anduril];

let backpack: Container.container = {
  size: (PositiveInt(5), PositiveInt(12)),
  items: [],
};
