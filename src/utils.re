include Belt;

let text = ReasonReact.string;

type nonNegativeInt =
  | NonNegativeInt(int);

let createNonNegativeInt = number => {
  switch (number) {
  | x when x >= 0 => Some(NonNegativeInt(x))
  | _ => None
  };
};

let intFromNonNegativeInt = nonNegativeInt => {
  switch (nonNegativeInt) {
  | NonNegativeInt(i) => i
  };
};

type positiveInt =
  | PositiveInt(int);

let createPositiveInt = number => {
  switch (number) {
  | x when x > 0 => Some(PositiveInt(x))
  | _ => None
  };
};

let intFromPositiveInt = positiveInt => {
  switch (positiveInt) {
  | PositiveInt(i) => i
  };
};

type coords = (nonNegativeInt, nonNegativeInt);

let createCoords = (x: nonNegativeInt, y: nonNegativeInt) => (x, y);

let coordsToInts = (coords: coords) => {
  let (x, y) = coords;
  (intFromNonNegativeInt(x), intFromNonNegativeInt(y));
};

type size = (positiveInt, positiveInt);

let createSize = (~h: positiveInt, ~w: positiveInt): size => (h, w);

let sizeToInts = (size: size) => {
  let (h, w) = size;
  (intFromPositiveInt(h), intFromPositiveInt(w));
};

let areaFromSize = (size: size) => {
  let (h, w) = size;
  let (h, w) = (intFromPositiveInt(h), intFromPositiveInt(w));

  h * w;
};
