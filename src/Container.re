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
  | ((itemAH, itemAW), _, coords, items) =>
    items->List.every(({origin, item: {size}}) => {
      let (minXA, minYA) = coords;
      let (maxXA, maxYA) = (minXA + itemAW, minYA + itemAH);
      let (itemBH, itemBW) = size;
      let (minXB, minYB) = origin;
      let (maxXB, maxYB) = (minXB + itemBW, minYB + itemBH);

      /*
        2d rectangle collision detection
        Shamlessly copy/pasted from:
        https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection#Axis-Aligned_Bounding_Box
       */

      !(minXA < maxXB && maxXA > minXB && minYA < maxYB && maxYA > minYB);
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
