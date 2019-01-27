open Utils;
open Items;

type placedItem = {
  item: Items.item,
  origin: Coords.t,
};

type container = {
  size: Size.t,
  items: list(placedItem),
};

let defaultContainer = {size: (1, 1), items: []};

let createContainer = size => {size, items: []};

let createContainerFromScratch = (~w, ~h) => {
  switch (PositiveInt.make(h), PositiveInt.make(w)) {
  | (Some(h), Some(w)) => {size: Size.make(~h, ~w), items: []}
  | _ => defaultContainer
  };
};

let canAddItemToContainerAtCoords = (~item: item, ~container, ~coords) => {
  switch (
    item.size->Size.toIntTuple,
    container.size->Size.toIntTuple,
    coords->Coords.toIntTuple,
    container.items,
  ) {
  | ((itemH, _), (containerH, _), _, _) when itemH > containerH => false
  | ((_, itemW), (_, containerW), _, _) when itemW > containerW => false
  | ((iH, _), (cH, _), (_, y), _) when cH < iH + y => false
  | ((_, iW), (_, cW), (x, _), _) when cW < iW + x => false
  | (_, _, coords, items) =>
    items->List.every(({origin, item: {size}}) => {
      let (minX, minY) = origin->Coords.toIntTuple;
      let (h, w) = size->Size.toIntTuple;
      switch (coords, (minX, minX + w), (minY, minY + h)) {
      | ((x, y), (minX, maxX), (minY, maxY))
          when x >= minX && y >= minY && x < maxX && y < maxY =>
        false
      | _ => true
      };
    })
  };
};

let tryToAddItemToContainer = (~item, ~container, ~coords) => {
  switch (canAddItemToContainerAtCoords(~item, ~container, ~coords)) {
  | true =>
    Result.Ok({
      ...container,
      items: container.items->List.add({item, origin: coords}),
    })
  | _ => Result.Error(("Could not add item to container", container))
  };
};
