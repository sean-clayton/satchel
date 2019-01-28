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
  description: "A small sword, not much larger than a dagger, that glows when orcs or goblins are nearby.",
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/OneHandSwords/OneHandSword4.png",
    ),
  rarity: Epic,
  kind: Weapon(OneHanded(ShortSword)),
  size: (3, 2),
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

let morgulBlade = {
  id: createItemId(),
  name: "Morgul Blade",
  description: "A magical and poisonous dagger.",
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Weapons/OneHandWeapons/Daggers/Dagger8.png",
    ),
  rarity: Rare,
  kind: Weapon(OneHanded(Dagger)),
  size: (3, 1),
};

let urukHaiChestPiece = {
  id: createItemId(),
  name: "Uruk Hai Chestpiece",
  description: "Body armor worn by the Uruk Hai of Isengard.",
  image:
    ItemImage.make(
      "https://web.poecdn.com/image/Art/2DItems/Armours/BodyArmours/BodyStr1A.png",
    ),
  rarity: Uncommon,
  kind: Apparel(Chestpiece),
  size: (3, 2),
};

let predefinedItems = [
  sting,
  anduril,
  theOneRing,
  morgulBlade,
  urukHaiChestPiece,
];

let backpack: Container.container = {size: (20, 20), items: []};
