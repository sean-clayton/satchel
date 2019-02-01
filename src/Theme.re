open Items.Quality;
open Styles.Functions;

module Colors = {
  type t =
    | Black
    | White;

  let qualityRgbTuple = quality =>
    switch (quality) {
    | Junk => (160, 160, 160)
    | Common => (241, 225, 196)
    | QuestRelated => (60, 60, 255)
    | Uncommon => (15, 230, 32)
    | Rare => (60, 190, 255)
    | Mythical => (255, 70, 255)
    | Legendary => (255, 192, 2)
    };

  let qualityAlpha = (quality, alpha) =>
    qualityRgbTuple(quality)->rgbToRgba(alpha);

  let quality = quality => qualityAlpha(quality, 1.);
};
