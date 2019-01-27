open Items;

let anduril = {
  id: createItemId(),
  name: {js|Andúril|js},
  description: "A longsword reforged from the shards of Narsil.",
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/TwoHandWeapons/TwoHandSwords/TwoHandSword3.png",
    ),
  rarity: Legendary,
  kind: Weapon(TwoHanded(Sword)),
  size: (4, 2),
};

let sting = {
  id: createItemId(),
  name: "Sting",
  description: "A short sword that glows when orcs or goblins are nearby.",
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/OneHandSwords/OneHandSword4.png",
    ),
  rarity: Exotic,
  kind: Weapon(OneHanded(ShortSword)),
  size: (2, 1),
};

let theOneRing = {
  id: createItemId(),
  name: "The One Ring",
  description: {|A small golden ring. When exposed to flame, an inscription in black speech reads: "One ring to rule them all, one ring to find them, one ring to bring them all and in the darkness bind them."|},
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Rings/Ring4.png",
    ),
  rarity: Legendary,
  kind: Apparel(Ring),
  size: (1, 1),
};

let predefinedItems = [sting, anduril, theOneRing];

let backpack: Container.container = {size: (5, 1), items: []};
