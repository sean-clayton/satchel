include Belt;

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

let coordsToInts = (coords: coords) => {
  let (x, y) = coords;
  (intFromNonNegativeInt(x), intFromNonNegativeInt(y));
};

type size = (positiveInt, positiveInt);

let sizeToInts = (size: size) => {
  let (h, w) = size;
  (intFromPositiveInt(h), intFromPositiveInt(w));
};

let areaFromSize = (size: size) => {
  let (h, w) = size;
  let (h, w) = (intFromPositiveInt(h), intFromPositiveInt(w));

  h * w;
};

let createCoords = (x, y) => {
  let x = createNonNegativeInt(x);
  let y = createNonNegativeInt(y);

  switch (x, y) {
  | (Some(x), Some(y)) => Some((x, y): coords)
  | _ => None
  };
};
