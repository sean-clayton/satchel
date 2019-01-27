open Utils;
open Items;

type placedItem = {
  item: Items.item,
  origin: coords,
};

type container = {
  size,
  items: list(placedItem),
};

let defaultContainer = {size: (PositiveInt(1), PositiveInt(1)), items: []};

let createContainer = size => {size, items: []};

let createContainerFromScratch = (~w, ~h) => {
  switch (createPositiveInt(h), createPositiveInt(w)) {
  | (Some(h), Some(w)) => {size: createSize(~h, ~w), items: []}
  | _ => defaultContainer
  };
};

let canAddItemToContainerAtCoords = (~item: item, ~container, ~coords) => {
  let itemSizeInts = item.size->sizeToInts;
  let containerSizeInts = container.size->sizeToInts;
  let coordsInts = coords->coordsToInts;

  switch (itemSizeInts, containerSizeInts, container.items) {
  | ((itemH, _), (containerH, _), _) when itemH > containerH => false
  | ((_, itemW), (_, containerW), _) when itemW > containerW => false
  | (_, _, items) =>
    items->List.every(({origin, item: {size}}) => {
      let (minX, minY) = origin->coordsToInts;
      let (h, w) = size->sizeToInts;
      switch (coordsInts, (minX, minX + w), (minY, minY + h)) {
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
    Some({
      ...container,
      items: container.items->List.add({item, origin: coords}),
    })
  | _ => None
  };
};
