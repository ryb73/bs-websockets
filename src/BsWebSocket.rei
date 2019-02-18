module CloseEvent: {
    type t;
    type code =
        | NormalClosure | GoingAway | ProtocolError | UnsupportedData | NoStatusRecvd
        | AbnormalClosure | InvalidFramePayloadData | PolicyViolation | MessageTooBig
        | MissingExtension | InternalError | ServiceRestart | TryAgainLater
        | BadGateway | TLSHandshake | Custom(int);
    let code: t => code;
    let reason: t => string;
    let wasClean: t => bool;
};
module MessageEvent: {
    type t;
    let data: t => string;
    let origin: t => string;
};
module ErrorEvent: { type t; };
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
