open BsWebSocket;

let ws = make("wss://echo.websocket.org");

let send = (ws, msg) =>
    Js.Global.setTimeout(() => BsWebSocket.send(ws, msg), 2000)
    |> ignore;

onError(ws, Js.log2("error"));
onOpen(ws, e => {
    onClose(ws, e => {
        Js.log2("Close", e);
        Js.log2("code", CloseEvent.code(e));
        Js.log2("reason", CloseEvent.reason(e));
        Js.log2("wasClean", CloseEvent.wasClean(e));
    });

    Js.log2("Open", e);
    send(ws, "one");
});
onMessage(ws, e => {
    Js.log4("Message", MessageEvent.data(e), MessageEvent.origin(e), e);
    Js.log2("rs:", readyState(ws));

    switch (MessageEvent.data(e)) {
        | "one" => send(ws, "two")
        | "two" => send(ws, Js.Json.stringifyAny({"m":3}) |> Belt.Option.getExn)
        | "{\"m\":3}" => close(~code=CloseEvent.Custom(4321), ~reason="idk", ws)
        | _ => ()
    };
});

Js.log2("url:", url(ws));
Js.log2("connecting?", readyState(ws) == Connecting);
