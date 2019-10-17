

var webi = {};



function webi_on_button(button_id) {
    var msg = {target: "input",
	       type: "button",
	       id: button_id,
	       eventType: "onclick",
    };
    document.webSocket.send(JSON.stringify(msg));
}

webi.on_button = webi_on_button;


webi.on_websocket_message = function(e) {
    let obj = JSON.parse(e.data);
    
};


document.addEventListener("DOMContentLoaded", function(e) {
	webSocket = new WebSocket("ws://localhost:8081");

	webSocket.addEventListener('open',function(e){
		console.log('Socke Connection Success');
		console.log(e);
	    });

	webSocket.addEventListener('message',function(e){
		console.log(e.data);
		webi.on_websocket_message(e);
	    });
	document.webSocket = webSocket;
    });

