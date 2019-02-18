type t;

type code =
    | NormalClosure | GoingAway | ProtocolError | UnsupportedData | NoStatusRecvd
    | AbnormalClosure | InvalidFramePayloadData | PolicyViolation | MessageTooBig
    | MissingExtension | InternalError | ServiceRestart | TryAgainLater | BadGateway
    | TLSHandshake | Custom(int);

let code_encode = fun
    | NormalClosure => Js.Json.number(1000.)
    | GoingAway => Js.Json.number(1001.)
    | ProtocolError => Js.Json.number(1002.)
    | UnsupportedData => Js.Json.number(1003.)
    | NoStatusRecvd => Js.Json.number(1005.)
    | AbnormalClosure => Js.Json.number(1006.)
    | InvalidFramePayloadData => Js.Json.number(1007.)
    | PolicyViolation => Js.Json.number(1008.)
    | MessageTooBig => Js.Json.number(1009.)
    | MissingExtension => Js.Json.number(1010.)
    | InternalError => Js.Json.number(1011.)
    | ServiceRestart => Js.Json.number(1012.)
    | TryAgainLater => Js.Json.number(1013.)
    | BadGateway => Js.Json.number(1014.)
    | TLSHandshake => Js.Json.number(1015.)
    | Custom(i) => Js.Json.number(i |> float_of_int);

let code_decode = (json) =>
    switch (Js.Json.decodeNumber(json)) {
        | None => Js.Exn.raiseError("Unexpected code: " ++ Js.String.make(json))
        | Some(1000.) => NormalClosure
        | Some(1001.) => GoingAway
        | Some(1002.) => ProtocolError
        | Some(1003.) => UnsupportedData
        | Some(1005.) => NoStatusRecvd
        | Some(1006.) => AbnormalClosure
        | Some(1007.) => InvalidFramePayloadData
        | Some(1008.) => PolicyViolation
        | Some(1009.) => MessageTooBig
        | Some(1010.) => MissingExtension
        | Some(1011.) => InternalError
        | Some(1012.) => ServiceRestart
        | Some(1013.) => TryAgainLater
        | Some(1014.) => BadGateway
        | Some(1015.) => TLSHandshake
        | Some(i) => Custom(i |> int_of_float)
    };

[@bs.get] external code: t => Js.Json.t = "";
let code = (ws) => code(ws) |> code_decode;

[@bs.get] external reason: t => string = "";
[@bs.get] external wasClean: t => bool = "";
