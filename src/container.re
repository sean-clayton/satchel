open Utils;

type placedItem = {
  item: Items.item,
  origin: coords,
};

type container = {
  size: (positiveInt, positiveInt),
  items: list(placedItem),
};

let canAddItemToContainerAtCoords = (item, container, coords) => {
  let itemSizeInts = item.item.size->sizeToInts;
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

let addItemToContainer = (item, container, coords) => {
  ...container,
  items: [{item, origin: coords}, ...container.items],
};
