/* This module is named BsWebSocket in order to avoid polluting the JS namespace */

type t;

module CloseEvent = CloseEvent;
module ErrorEvent = { type t; };
module MessageEvent = MessageEvent;
module OpenEvent = { type t; };

[@bs.new] external make: (string, ~protocols: array(string)=?, unit) => t = "WebSocket";
let make = (~protocols=?, url) => make(url, ~protocols?, ());

[@bs.set] external onClose: t => (CloseEvent.t => unit) => unit = "onclose";
[@bs.set] external onError: t => (ErrorEvent.t => unit) => unit = "onerror";
[@bs.set] external onMessage: t => (MessageEvent.t => unit) => unit = "onmessage";
[@bs.set] external onOpen: t => (OpenEvent.t => unit) => unit = "onopen";

[@bs.get] external url: t => string = "";

[@bs.deriving jsConverter]
type readyState =
    | [@bs.as 0] Connecting | [@bs.as 1] Open
    | [@bs.as 2] Closing | [@bs.as 3] Closed;
[@bs.get] external readyState: t => int = "";
let readyState = (ws) => readyState(ws) |> readyStateFromJs |> Belt.Option.getExn;

[@bs.send.pipe: t] external close: ~code:Js.Json.t=? => ~reason:string=? => unit = "";
let close = (~code=?, ~reason=?, ws) =>
    close(
        ~code=?Belt.Option.map(code, CloseEvent.code_encode),
        ~reason?, ws
    );

[@bs.send] external send: t => string => unit = "";
