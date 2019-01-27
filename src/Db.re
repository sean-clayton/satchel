open Utils;
open Items;

let anduril = {
  id: createItemId(),
  name: {js|Andúril|js},
  description: "A longsword reforged from the shards of Narsil.",
  image:
    ItemImage(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/TwoHandWeapons/TwoHandSwords/TwoHandSword3.png",
    ),
  rarity: Legendary,
  kind: Weapon(TwoHanded(Sword)),
  size: (PositiveInt(4), PositiveInt(2)),
};

let sting = {
  id: createItemId(),
  name: "Sting",
  description: "A short sword that glows when orcs or goblins are nearby.",
  image:
    ItemImage(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/OneHandSwords/OneHandSword4.png",
    ),
  rarity: Exotic,
  kind: Weapon(OneHanded(ShortSword)),
  size: (PositiveInt(2), PositiveInt(1)),
};

let theOneRing = {
  id: createItemId(),
  name: "The One Ring",
  description: {|A small golden ring. When exposed to flame, an inscription in black speech reads: "One ring to rule them all, one ring to find them, one ring to bring them all and in the darkness bind them."|},
  image:
    ItemImage("https://web.poecdn.com/image/Art/2DItems/Rings/Ring4.png"),
  rarity: Legendary,
  kind: Apparel(Ring),
  size: (PositiveInt(1), PositiveInt(1)),
};

let predefinedItems = [sting, anduril, theOneRing];

let backpack: Container.container = {
  size: (PositiveInt(5), PositiveInt(12)),
  items: [],
};
