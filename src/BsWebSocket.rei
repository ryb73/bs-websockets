module CloseEvent = CloseEvent;
module ErrorEvent: { type t; };
module MessageEvent = MessageEvent;
module OpenEvent: { type t; };

type t;

let make: string => t;
let onClose: (t, CloseEvent.t => unit) => unit;
let onError: (t, ErrorEvent.t => unit) => unit;
let onMessage: (t, MessageEvent.t => unit) => unit;
let onOpen: (t, OpenEvent.t => unit) => unit;

let url: t => string;

type readyState = Connecting | Open | Closing | Closed;
let readyState: t => readyState;

let close: (~code: CloseEvent.code=?, ~reason: string=?, t) => unit;
let send: (t, string) => unit;
