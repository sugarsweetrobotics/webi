

var webi = {};



webi.on_button = function(button_id) {
    var msg = {target: "input",
	       type: "button",
	       id: button_id,
	       eventType: "onclick",
    };
    document.webSocket.send(JSON.stringify(msg));
}

webi.on_websocket_message = function(e) {
    let obj = JSON.parse(e.data);
    if (obj.type == "element") {
	webi.on_message_element(obj);
    }
};


webi.on_message_element = function(msg) {
    let e = document.getElementById(msg.id);
    if (e) {
	if (msg.cmd === "innerHTML") {
	    e.innerHTML = msg.arg;
	}
    }
}

webi.set_toolbar_status = function(flag) {
	let b = document.getElementById("webi-toolbar-status-on");
	if (b) {
	    b.style.display = flag ? "block" : "none";
	}
	let a = document.getElementById("webi-toolbar-status-off");
	if (a) {
	    a.style.display = flag ? "none" : "block";
	}
}

document.addEventListener("DOMContentLoaded", function(e) {
	webSocket = new WebSocket("ws://localhost:8081");

	webSocket.addEventListener('open',function(e){
		console.log('WebSocket Connection Success');
		webi.set_toolbar_status(true);
	    });

	webSocket.addEventListener('close',function(e){
		console.log('Socke Connection Success');
		webi.set_toolbar_status(false);
	    });

	webSocket.addEventListener('message',function(e){
		console.log(e.data);
		webi.on_websocket_message(e);
	    });
	document.webSocket = webSocket;
    });

