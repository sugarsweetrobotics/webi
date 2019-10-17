function webi_on_button(button_id) {
    var msg = { 
	target: "input",
	type: "button",
	id: button_id,
	eventType: "on_click",
    };
    document.webSocket.send(JSON.stringify(msg));
}


document.addEventListener("DOMContentLoaded", function(e) {
	webSocket = new WebSocket("ws://localhost:8081");

	webSocket.addEventListener('open',function(e){
		console.log('Socke Connection Success');
	    });

	webSocket.addEventListener('message',function(e){
		console.log(e.data);
	    });
	document.webSocket = webSocket;
    });

