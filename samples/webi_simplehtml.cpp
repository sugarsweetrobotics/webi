#include <iostream>

#include "webi/webi.h"

using namespace webi;

int main(void) {
	webi::Webi webi;

	auto server = webi.createServer();
	server->baseDirectory("../www");

	/// Create DOM reference.
	/// Through this reference, this application can change the state of browser's DOM remotely.
	auto document = server->createDocument();
	auto on_up_button_clicked = [&document](const ActionEvent& e) {
		std::cout << "Up Button Clicked" << std::endl;
		auto elem = document.getElementById("webi_content");
		elem.setInnerHTML("Value is Up");
	};
	auto on_down_button_clicked = [&document](const ActionEvent& e) {
		std::cout << "Down Button Clicked" << std::endl;
		auto elem = document.getElementById("webi_content");
		elem.setInnerHTML("Value is Down");
	};

	// Grid Style
	GridLayoutStyler style({ 20, 150, 30 }, { 40, 40 });

	// Define HTML file and set endpoint and document simaltaneously for server.
	server->get("/", HTML(
		Header(
			WebiScript(), // This is needed for webi framework.
			StyleSheet("webi.css")),
		Body(
			WebiToolbar(),
			H1(Text("This is Title")),
			P(ID("webi_content"),
				Text("This is Test Page of Webi")
			),
			DIV(style.containerStyle(),
				P(Text("Up button ->"), style.gridStyle(1, 0), Style("color:red;")),
				Button("Up", ID("button_up"), style.gridStyle(2, 0),
					EventListener("onclick", on_up_button_clicked)),
				P(Text("Down button ->"), style.gridStyle(1, 1), Style("color:blue;")),
				Button("Down", ID("button_down"), style.gridStyle(2, 1),
					EventListener("onclick", on_down_button_clicked))
			)
		)
	)
	);


	std::cout << "Server is started." << std::endl;
	// first param is for HTTP, second is for Websocket.
	server->runBackground(8080, 8081);

	server->waitBackground();
	
	return 0;
}
