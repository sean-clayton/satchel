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
    | Legendary
    | Mythical;

  let toString = quality =>
    switch (quality) {
    | Common => "Common"
    | Uncommon => "Uncommon"
    | Rare => "Rare"
    | Legendary => "Legendary"
    | Mythical => "Mythical"
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
  image: ItemImage.make("p43_retrosword_1h_001_demonhunter_male"),
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

let preloadImages = [
  "p43_retrosword_1h_001_demonhunter_male",
  "unique_sword_1h_010_x1_demonhunter_male",
  "sword_1h_203_demonhunter_male",
  "unique_sword_1h_017_x1_demonhunter_male",
  "unique_sword_1h_001_104_demonhunter_male",
  "sword_1h_107_demonhunter_male",
  "sword_1h_103_demonhunter_male",
  "transmogsword_241_003_demonhunter_male",
  "transmogsword_241_001_demonhunter_male",
  "unique_sword_1h_010_1xx_demonhunter_male",
  "sword_1h_106_demonhunter_male",
  "transmogsword_241_004_demonhunter_male",
  "sword_1h_206_demonhunter_male",
  "unique_sword_1h_109_x1_demonhunter_male",
  "unique_sword_1h_007_x1_demonhunter_male",
  "unique_sword_1h_010_demonhunter_male",
  "sword_1h_205_demonhunter_male",
  "unique_sword_1h_003_x1_demonhunter_male",
  "sword_1h_002_demonhunter_male",
  "sword_1h_105_demonhunter_male",
  "sword_1h_104_demonhunter_male",
  "p3_unique_sword_1h_104_demonhunter_male",
  "sword_1h_302_demonhunter_male",
  "unique_sword_1h_001_demonhunter_male",
  "transmogsword_241_002_demonhunter_male",
  "unique_sword_1h_014_x1_demonhunter_male",
  "sword_1h_008_demonhunter_male",
  "sword_1h_301_demonhunter_male",
  "p4_unique_sword_1h_01_demonhunter_male",
  "unique_sword_1h_019_x1_demonhunter_male",
  "unique_sword_1h_102_x1_demonhunter_male",
  "unique_sword_1h_001_1xx_demonhunter_male",
  "sword_1h_101_demonhunter_male",
  "sword_1h_003_demonhunter_male",
  "sword_1h_207_demonhunter_male",
  "transmogsword_241_005_demonhunter_male",
  "unique_sword_1h_018_x1_demonhunter_male",
  "unique_sword_1h_001_x1_demonhunter_male",
  "sword_1h_001_demonhunter_male",
  "sword_1h_202_demonhunter_male",
  "p61_unique_sword_1h_112_x1_demonhunter_male",
  "unique_sword_1h_002_x1_demonhunter_male",
  "unique_sword_1h_101_x1_demonhunter_male",
  "unique_sword_1h_set_03_x1_demonhunter_male",
  "unique_sword_1h_004_x1_demonhunter_male",
  "unique_sword_1h_113_x1_demonhunter_male",
  "sword_1h_208_demonhunter_male",
  "unique_sword_1h_011_x1_demonhunter_male",
  "unique_sword_1h_set_02_x1_demonhunter_male",
  "sword_1h_108_demonhunter_male",
  "unique_sword_1h_010_104_demonhunter_male",
  "sword_1h_201_demonhunter_male",
  "unique_sword_1h_018_1xx_demonhunter_male",
  "sword_1h_004_demonhunter_male",
  "p3_unique_sword_1h_012_demonhunter_male",
  "unique_sword_1h_019_1xx_demonhunter_male",
  "unique_sword_1h_promo_02_x1_demonhunter_male",
  "sword_1h_204_demonhunter_male",
  "sword_1h_006_demonhunter_male",
  "sword_1h_007_demonhunter_male",
  "unique_sword_1h_103_x1_demonhunter_male",
  "unique_sword_1h_107_x1_demonhunter_male",
  "sword_1h_102_demonhunter_male",
  "sword_1h_005_demonhunter_male",
  "p43_retrosword_002_demonhunter_male",
  "sword_2h_101_demonhunter_male",
  "unique_sword_2h_002_x1_demonhunter_male",
  "sword_2h_206_demonhunter_male",
  "sword_2h_001_demonhunter_male",
  "unique_sword_2h_008_x1_demonhunter_male",
  "sword_2h_005_demonhunter_male",
  "unique_sword_2h_001_x1_demonhunter_male",
  "unique_sword_2h_102_x1_demonhunter_male",
  "unique_sword_2h_004_x1_demonhunter_male",
  "sword_2h_204_demonhunter_male",
  "unique_sword_2h_011_x1_demonhunter_male",
  "sword_2h_105_demonhunter_male",
  "sword_2h_201_demonhunter_male",
  "sword_2h_103_demonhunter_male",
  "sword_2h_301_demonhunter_male",
  "unique_sword_2h_103_x1_demonhunter_male",
  "sword_2h_302_demonhunter_male",
  "unique_sword_2h_101_x1_demonhunter_male",
  "sword_2h_102_demonhunter_male",
  "sword_2h_203_demonhunter_male",
  "unique_sword_2h_010_x1_demonhunter_male",
  "sword_2h_106_demonhunter_male",
  "unique_sword_2h_104_x1_demonhunter_male",
  "p61_unique_sword_2h_007_x1_demonhunter_male",
  "unique_sword_2h_014_demonhunter_male",
  "sword_2h_104_demonhunter_male",
  "sword_2h_202_demonhunter_male",
  "p61_unique_sword_2h_012_x1_demonhunter_male",
  "unique_sword_2h_014_104_demonhunter_male",
  "sword_2h_003_demonhunter_male",
  "sword_2h_205_demonhunter_male",
  "unique_sword_2h_014_x1_demonhunter_male",
  "sword_2h_002_demonhunter_male",
  "unique_sword_2h_014_1xx_demonhunter_male",
  "sword_2h_006_demonhunter_male",
  "sword_2h_004_demonhunter_male",
  "unique_sword_2h_003_x1_demonhunter_male",
  "unique_chest_set_01_p1_demonhunter_male",
  "unique_chest_set_10_x1_demonhunter_male",
  "unique_chest_set_03_p3_demonhunter_male",
  "unique_chest_set_01_p2_demonhunter_male",
  "unique_chest_set_05_x1_demonhunter_male",
  "transmoghelm_002_demonhunter_male",
  "unique_helm_006_x1_demonhunter_male",
  "unique_helm_set_09_x1_demonhunter_male",
  "unique_helm_102_x1_demonhunter_male",
  "p43_retrohelm_003_demonhunter_male",
  "unique_helm_015_1xx_demonhunter_male",
  "unique_helm_002_p1_demonhunter_male",
  "unique_helm_012_1xx_demonhunter_male",
  "p43_retrohelm_001_demonhunter_male",
  "unique_helm_015_x1_demonhunter_male",
  "unique_helm_009_x1_demonhunter_male",
  "p4_unique_helm_102_demonhunter_male",
  "unique_helm_014_1xx_demonhunter_male",
  "unique_helm_103_x1_demonhunter_male",
  "unique_helm_011_x1_demonhunter_male",
  "unique_helm_set_11_x1_demonhunter_male",
  "unique_helm_012_x1_demonhunter_male",
  "unique_helm_004_x1_demonhunter_male",
  "unique_helm_010_x1_demonhunter_male",
  "unique_helm_016_1xx_demonhunter_male",
  "p4_unique_helm_103_demonhunter_male",
  "unique_helm_016_x1_demonhunter_male",
  "unique_helm_set_13_x1_demonhunter_male",
  "unique_helm_008_x1_demonhunter_male",
  "unique_helm_007_x1_demonhunter_male",
  "p2_unique_helm_001_demonhunter_male",
  "transmoghelm_001_demonhunter_male",
  "p43_retrohelm_002_demonhunter_male",
  "unique_helm_014_x1_demonhunter_male",
  "unique_helm_011_1xx_demonhunter_male",
  "unique_helm_set_12_x1_demonhunter_male",
  "unique_helm_003_p2_demonhunter_male",
  "unique_helm_set_14_x1_demonhunter_male",
  "unique_helm_set_15_x1_demonhunter_male",
  "dagger_204_demonhunter_male",
  "dagger_201_demonhunter_male",
  "dagger_202_demonhunter_male",
  "dagger_105_demonhunter_male",
  "dagger_104_demonhunter_male",
  "unique_dagger_008_demonhunter_male",
  "unique_dagger_010_x1_210_demonhunter_male",
  "dagger_206_demonhunter_male",
  "p61_unique_dagger_101_x1_demonhunter_male",
  "dagger_203_demonhunter_male",
  "unique_dagger_007_x1_demonhunter_male",
  "unique_dagger_008_104_demonhunter_male",
  "dagger_302_demonhunter_male",
  "unique_dagger_008_x1_demonhunter_male",
  "dagger_101_demonhunter_male",
  "dagger_207_demonhunter_male",
  "unique_dagger_104_x1_demonhunter_male",
  "unique_dagger_103_x1_demonhunter_male",
  "dagger_003_demonhunter_male",
  "p61_unique_dagger_102_x1_demonhunter_male",
  "unique_dagger_006_1xx_demonhunter_male",
  "dagger_004_demonhunter_male",
  "dagger_002_demonhunter_male",
  "dagger_102_demonhunter_male",
  "dagger_005_demonhunter_male",
  "dagger_106_demonhunter_male",
  "dagger_007_demonhunter_male",
  "dagger_107_demonhunter_male",
  "dagger_301_demonhunter_male",
  "dagger_103_demonhunter_male",
  "dagger_205_demonhunter_male",
  "unique_dagger_008_1xx_demonhunter_male",
  "unique_dagger_006_x1_demonhunter_male",
  "dagger_006_demonhunter_male",
  "dagger_001_demonhunter_male",
  "unique_ring_015_x1_demonhunter_male",
  "p61_unique_ring_03_demonhunter_male",
  "unique_ring_107_x1_demonhunter_male",
  "unique_ring_024_x1_demonhunter_male",
  "unique_ring_013_x1_demonhunter_male",
  "ring_20_demonhunter_male",
  "unique_ring_014_x1_demonhunter_male",
  "unique_ring_set_001_x1_demonhunter_male",
  "unique_ring_109_x1_demonhunter_male",
  "ring_04_demonhunter_male",
  "ring_18_demonhunter_male",
  "ph_ring_demonhunter_male",
  "unique_ring_108_x1_demonhunter_male",
  "ring_09_demonhunter_male",
  "p61_unique_ring_02_demonhunter_male",
  "unique_ring_023_p2_demonhunter_male",
  "ring_25_demonhunter_male",
  "unique_ring_101_x1_demonhunter_male",
  "unique_ring_001_x1_demonhunter_male",
  "ring_16_demonhunter_male",
  "ring_08_demonhunter_male",
  "p61_unique_ring_05_demonhunter_male",
  "ring_02_demonhunter_male",
  "unique_ring_006_p2_demonhunter_male",
  "ring_10_demonhunter_male",
  "p42_unique_ring_haunt_demonhunter_male",
  "ring_07_demonhunter_male",
  "unique_ring_003_x1_demonhunter_male",
  "ring_21_demonhunter_male",
  "unique_ring_002_x1_demonhunter_male",
  "p43_unique_ring_021_x1_demonhunter_male",
  "ring_01_demonhunter_male",
  "ring_13_demonhunter_male",
  "unique_ring_109_p2_demonhunter_male",
  "ring_24_demonhunter_male",
  "unique_ring_104_x1_demonhunter_male",
  "p2_unique_ring_03_demonhunter_male",
  "p4_unique_ring_03_demonhunter_male",
  "p4_unique_ring_02_demonhunter_male",
  "ring_06_demonhunter_male",
  "p6_unique_ring_02_demonhunter_male",
  "ring_15_demonhunter_male",
  "p43_retroring_002_demonhunter_male",
  "p6_unique_ring_01_demonhunter_male",
  "ring_14_demonhunter_male",
  "ring_05_demonhunter_male",
  "unique_ring_106_x1_demonhunter_male",
  "unique_ring_020_x1_demonhunter_male",
  "unique_ring_set_002_x1_demonhunter_male",
  "unique_ring_012_x1_demonhunter_male",
  "p43_retroring_001_demonhunter_male",
  "ring_19_demonhunter_male",
  "unique_ring_103_x1_demonhunter_male",
  "ring_23_demonhunter_male",
  "unique_ring_004_x1_demonhunter_male",
  "ring_12_demonhunter_male",
  "unique_ring_102_p2_demonhunter_male",
  "unique_ring_024_104_demonhunter_male",
  "ring_11_demonhunter_male",
  "unique_ring_007_p1_demonhunter_male",
  "ring_17_demonhunter_male",
  "unique_ring_019_x1_demonhunter_male",
  "unique_ring_010_x1_demonhunter_male",
  "p6_unique_ring_03_demonhunter_male",
  "unique_ring_017_p4_demonhunter_male",
  "ring_03_demonhunter_male",
  "unique_ring_011_x1_demonhunter_male",
  "p2_unique_ring_wizard_001_demonhunter_male",
  "p6_unique_ring_04_demonhunter_male",
  "p61_unique_ring_01_demonhunter_male",
  "ring_22_demonhunter_male",
  "unique_ring_018_p2_demonhunter_male",
  "p2_unique_ring_04_demonhunter_male",
  "unique_chest_001_x1_demonhunter_male",
  "unique_chest_set_09_x1_demonhunter_male",
  "unique_chest_025_1xx_demonhunter_male",
  "unique_chest_101_x1_demonhunter_male",
  "unique_chest_016_x1_demonhunter_male",
  "unique_chest_013_x1_demonhunter_male",
  "unique_chest_019_x1_demonhunter_male",
  "unique_chest_026_1xx_demonhunter_male",
  "unique_chest_027_x1_demonhunter_male",
  "unique_chestarmor_028_x1_demonhunter_male",
  "unique_chest_027_1xx_demonhunter_male",
  "p4_unique_chest_012_demonhunter_male",
  "unique_chest_102_x1_demonhunter_male",
  "unique_chest_014_x1_demonhunter_male",
  "p43_retroarmor_001_demonhunter_male",
  "unique_chest_002_x1_demonhunter_male",
  "unique_chest_set_15_x1_demonhunter_male",
  "unique_chest_025_x1_demonhunter_male",
  "unique_chest_010_x1_demonhunter_male",
  "p43_retroarmor_002_demonhunter_male",
  "p4_unique_chest_018_demonhunter_male",
  "unique_chest_set_14_x1_demonhunter_male",
  "unique_chest_006_x1_demonhunter_male",
  "unique_chest_026_x1_demonhunter_male",
  "unique_chest_set_11_x1_demonhunter_male",
  "unique_chest_015_x1_demonhunter_male",
  "unique_chest_set_13_x1_demonhunter_male",
  "unique_chest_019_1xx_demonhunter_male",
  "chestarmor_104_demonhunter_male",
  "chestarmor_006_demonhunter_male",
  "chestarmor_001_demonhunter_male",
  "chestarmor_102_demonhunter_male",
  "chestarmor_005_demonhunter_male",
  "chestarmor_002_demonhunter_male",
  "chestarmor_103_demonhunter_male",
  "chestarmor_003_demonhunter_male",
  "chestarmor_002a_demonhunter_male",
  "chestarmor_206_demonhunter_male",
  "ph_chestarmor_demonhunter_male",
  "chestarmor_105_demonhunter_male",
  "chestarmor_208_demonhunter_male",
  "chestarmor_204_demonhunter_male",
  "chestarmor_207_demonhunter_male",
  "chestarmor_004_demonhunter_male",
  "chestarmor_203_demonhunter_male",
  "chestarmor_201_demonhunter_male",
  "chestarmor_202_demonhunter_male",
  "chestarmor_205_demonhunter_male",
  "chestarmor_101_demonhunter_male",
  "chestarmor_005a_demonhunter_male",
];
