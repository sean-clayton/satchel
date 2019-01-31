open Items;

let predefinedItems = [
  {
    id: createItemId(),
    name: "The One Ring",
    description: {|A small golden ring. When exposed to flame, an inscription in black speech reads: "One ring to rule them all, one ring to find them, one ring to bring them all and in the darkness bind them."|},
    image: ItemImage.make("ring_20_demonhunter_male"),
    rarity: Legendary,
    kind: Apparel(Ring),
    size: (1, 1),
  },
  {
    id: createItemId(),
    name: "Morgul Blade",
    description: "A magical and poisonous dagger.",
    image: ItemImage.make("unique_dagger_007_x1_demonhunter_male"),
    rarity: Rare,
    kind: Weapon(OneHanded(Dagger)),
    size: (2, 1),
  },
  {
    id: createItemId(),
    name: {js|Andúril|js},
    description: "A longsword reforged from the shards of Narsil.",
    image: ItemImage.make("sword_2h_101_demonhunter_male"),
    rarity: Legendary,
    kind: Weapon(TwoHanded(Sword)),
    size: (2, 1),
  },
  {
    id: createItemId(),
    name: "Sting",
    description: "A small sword, not much larger than a dagger, that glows when orcs or goblins are nearby.",
    image: ItemImage.make("unique_sword_1h_001_demonhunter_male"),
    rarity: Epic,
    kind: Weapon(OneHanded(ShortSword)),
    size: (2, 1),
  },
  {
    id: createItemId(),
    name: "Uruk Hai Chestpiece",
    description: "Body armor worn by the Uruk Hai of Isengard.",
    image: ItemImage.make("unique_chest_025_1xx_demonhunter_male"),
    rarity: Uncommon,
    kind: Apparel(Chestpiece),
    size: (2, 1),
  },
];

let backpack: Container.container = {size: (6, 10), items: []};
