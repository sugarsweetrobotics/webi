

var webi = {};

webi.on_websocket_message = function(e) {
	let obj = JSON.parse(e.data);
	if (obj.type == "element") {
		webi.on_message_element(obj);	
	}
};

webi.on_action_event = function (target, type, eventType, id, value) {

	var msg = {
		target: target,
		type: type,
		id: id,
		eventType: eventType,
    };

    if (typeof (value) !== 'undefined') {
        msg.value = value;
    }
	document.webSocket.send(JSON.stringify(msg));
}

webi.on_message_event = function(id, value) {
	var msg = {
		id: id,
		value: value,
	}
	document.webSocket.send(JSON.stringify(msg));
}

webi.on_message_element = function(msg) {
    let e = document.getElementById(msg.id);
    if (e) {
		if (msg.cmd === "innerHTML") {
			if (msg.dir == "set") {
				e.innerHTML = msg.arg;
			} else if (msg.dir == "get") {
				webi.on_message_event(msg.id, e.innerHTML);
			}
		}
		if (msg.cmd === "value") {
			if (msg.dir == "set") {
				e.value = msg.arg;
			} else if (msg.dir == "get") {
				webi.on_message_event(msg.id, e.value);
			}
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

    var s = $("volume1").slider().data("slider");
});

