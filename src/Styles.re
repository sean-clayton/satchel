open Css;

module Functions = {
  let rgbToRgba = (rgb: (int, int, int), alpha: float) => {
    let (r, g, b) = rgb;
    rgba(r, g, b, alpha);
  };
};
