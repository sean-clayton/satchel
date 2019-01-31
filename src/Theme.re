open Items.Rarity;
open Styles.Functions;

module Colors = {
  type t =
    | Black
    | White;

  let rarityRgbTuple = rarity =>
    switch (rarity) {
    | Common => (162, 160, 161)
    | Uncommon => (9, 253, 3)
    | Rare => (0, 119, 255)
    | Epic => (255, 28, 174)
    | Legendary => (255, 224, 2)
    };

  let rarityAlpha = (rarity, alpha) =>
    rarityRgbTuple(rarity)->rgbToRgba(alpha);

  let rarity = rarity => rarityAlpha(rarity, 1.);
};
