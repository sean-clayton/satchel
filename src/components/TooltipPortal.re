open Webapi.Dom;
open Utils;

let component = ReasonReact.statelessComponent("TooltipPortal");

let el = DocumentRe.getElementById("tooltip", document)->Option.getExn;

let make = children => {
  ...component,
  render: _self => {
    ReactDOMRe.createPortal(children, el);
  },
};
