open Css;
open Items;

module Colors = {
  let rarity = (rarity: Rarity.t) =>
    switch (rarity) {
    | Common => "a2a0a1"->hex
    | Uncommon => "09fd03"->hex
    | Rare => "0099ff"->hex
    | Epic => "5f059c"->hex
    | Legendary => "ffe002"->hex
    };
};
