open Items.Quality;
open Styles.Functions;

module Colors = {
  type t =
    | Black
    | White;

  let qualityRgbTuple = quality =>
    switch (quality) {
    | Common => (162, 160, 161)
    | Uncommon => (15, 230, 32)
    | Rare => (60, 190, 255)
    | Mythical => (255, 70, 255)
    | Legendary => (255, 192, 2)
    };

  let qualityAlpha = (quality, alpha) =>
    qualityRgbTuple(quality)->rgbToRgba(alpha);

  let quality = quality => qualityAlpha(quality, 1.);
};
