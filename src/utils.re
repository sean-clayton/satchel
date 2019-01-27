include Belt;

let text = ReasonReact.string;

module NonNegativeInt = {
  type t = int;
  let make = (num): option(t) =>
    switch (num) {
    | x when x >= 0 => Some(x)
    | _ => None
    };
  let toInt = (num: t): int => num;
};

module PositiveInt = {
  type t = int;
  let make = (num): option(t) =>
    switch (num) {
    | x when x > 0 => Some(x)
    | _ => None
    };
  let toInt = (num: t): int => num;
};

module Coords = {
  type t = (NonNegativeInt.t, NonNegativeInt.t);
  let make = (~x: NonNegativeInt.t, ~y: NonNegativeInt.t): t => (x, y);
  let toIntTuple = ((x: NonNegativeInt.t, y: NonNegativeInt.t)) => (
    NonNegativeInt.toInt(x),
    NonNegativeInt.toInt(y),
  );
};

module Size = {
  type t = (PositiveInt.t, PositiveInt.t);
  let make = (~h: PositiveInt.t, ~w: PositiveInt.t): t => (h, w);
  let toIntTuple = ((h: PositiveInt.t, y: PositiveInt.t)) => (
    PositiveInt.toInt(h),
    PositiveInt.toInt(y),
  );
  let area = (size: t) => {
    let (h, w) = toIntTuple(size);

    h * w;
  };
};
