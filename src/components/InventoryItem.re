open Items;

module Styles = {
  open Css;

  let imageContainerBase =
    style([
      display(inlineFlex),
      justifyContent(center),
      transitionTimingFunction(easeInOut),
      transitionDuration(80),
      transitionProperty("box-shadow, background-color"),
    ]);

  let imageContainer = item => {
    let (h, w) = item.size;
    let (o1, o2, o3, o4, o5, o6, o7, pct1) =
      switch (item.quality) {
      | Junk => (0.05, 0.05, 0., 0.05, 0.15, 0.25, 0.4, 0)
      | QuestRelated
      | Legendary => (0.5, 0.15, 0.25, 0.5, 0.5, 0.5, 1., 50)
      | _ => (0.1, 0.05, 0., 0.15, 0.25, 0.5, 1., 25)
      };

    style([
      height((h * 64)->px),
      width((w * 64)->px),
      backgroundColor(Theme.Colors.qualityAlpha(item.quality, o2)),
      backgroundImage(
        linearGradient(
          180->deg,
          [
            (pct1, Theme.Colors.qualityAlpha(item.quality, o3)),
            (100, Theme.Colors.qualityAlpha(item.quality, o1)),
          ],
        ),
      ),
      boxShadows([
        boxShadow(~inset=true, ~spread=1->px, black),
        boxShadow(
          ~inset=true,
          ~spread=2->px,
          Theme.Colors.qualityAlpha(item.quality, o6),
        ),
      ]),
      hover([
        backgroundColor(Theme.Colors.qualityAlpha(item.quality, o4)),
        boxShadows([
          boxShadow(~inset=true, ~spread=1->px, black),
          boxShadow(
            ~inset=true,
            ~spread=2->px,
            Theme.Colors.qualityAlpha(item.quality, o7),
          ),
          boxShadow(
            ~inset=true,
            ~blur=0.5->rem,
            Theme.Colors.quality(item.quality),
          ),
          boxShadow(
            ~blur=1.0->rem,
            Theme.Colors.qualityAlpha(item.quality, o5),
          ),
        ]),
      ]),
    ]);
  };

  let image = style([alignSelf(center)]);
};

type state = {
  showTooltip: bool,
  tooltipX: int,
  tooltipY: int,
};

type actions =
  | ShowTooltip
  | HideTooltip
  | MoveTooltip(int, int);

let component = ReasonReact.reducerComponent("InventoryItem");

let make = (~item, _children) => {
  ...component,
  initialState: () => {showTooltip: false, tooltipX: 0, tooltipY: 0},
  reducer: (action, state) =>
    switch (action) {
    | ShowTooltip => ReasonReact.Update({...state, showTooltip: true})
    | HideTooltip =>
      ReasonReact.Update({tooltipX: 0, tooltipY: 0, showTooltip: false})
    | MoveTooltip(tooltipX, tooltipY) =>
      ReasonReact.Update({...state, tooltipX, tooltipY})
    },
  render: self => {
    let (x, y) = (self.state.tooltipX, self.state.tooltipY);
    let onMouseEnter = e => {
      e->ReactEvent.Mouse.preventDefault;
      self.send(ShowTooltip);
    };
    let onMouseLeave = e => {
      e->ReactEvent.Mouse.preventDefault;
      self.send(HideTooltip);
    };
    let onMouseMove = e => {
      e->ReactEvent.Mouse.preventDefault;
      let x = e->ReactEvent.Mouse.clientX;
      let y = e->ReactEvent.Mouse.clientY;
      self.send(MoveTooltip(x, y));
    };
    <>
      <div
        onMouseEnter
        onMouseLeave
        onMouseMove
        className=Styles.(
          Css.merge([imageContainerBase, imageContainer(item)])
        )>
        <img
          className=Styles.image
          src={item.image->ItemImage.toString}
          alt={item.description}
        />
      </div>
      {switch (self.state.showTooltip) {
       | true =>
         <TooltipPortal>
           ...<InventoryItemInfoTooltip x y item />
         </TooltipPortal>
       | _ => ReasonReact.null
       }}
    </>;
  },
};
