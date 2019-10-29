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
		auto textBox01 = document.getElementById("text_01");
		auto elem = document.getElementById("webi_content");
		textBox01.getValue([elem](const webi::ElementResponse& res) {
			elem.setInnerHTML("Value is " + res.value);
		});
	};
	auto on_down_button_clicked = [&document](const ActionEvent& e) {
		std::cout << "Down Button Clicked" << std::endl;
		auto elem = document.getElementById("webi_content");
		elem.setInnerHTML("Value is Down");
	};

	// Grid Style
	GridLayoutStyler gridStyle({ 150, 150, 30 }, { 40, 40 });

	// Define HTML file and set endpoint and document simaltaneously for server.
	server->get("/", html(
		head(
			WebiScript(), // This is needed for webi framework.
			styleSheet("webi.css")),
		body(
			WebiToolbar(),
			h1(text("This is Title")),
			p(id("webi_content"),
				text("This is Test Page of Webi")
			),
			div(gridStyle.containerStyle(),
				p(text("Up button ->"), gridStyle.gridStyle(0, 0), style("color:red;")),
				textBox("TextBox1", id("text_01"), gridStyle.gridStyle(1, 0)),
				button("Up", id("button_up"), gridStyle.gridStyle(2, 0),
					EventListener("onclick", on_up_button_clicked)),
				p(text("Down button ->"), gridStyle.gridStyle(0, 1), style("color:blue;")),
				textBox("TextBox2", id("text_02"), gridStyle.gridStyle(1, 1)),
				button("Down", id("button_down"), gridStyle.gridStyle(2, 1),
					EventListener("onclick", on_down_button_clicked))
			)
		)
	)
	);


	std::cout << "Server is started." << std::endl;
	// first param is for HTTP, second is for Websocket.
	server->runBackground(8080, 8081);


	/// Do something



	server->waitBackground();
	
	return 0;
}
