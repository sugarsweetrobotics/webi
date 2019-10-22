#include <iostream>

#include "webi/webi.h"
#include "webi/bootstrap.h"

using namespace webi;


int main(void) {
	webi::Webi webi;


	auto s = webi.createServer();
	//auto document = s->createDocument();
	s->baseDirectory("../www");

	/*
	GridLayoutStyler style({ 20, 150, 30 }, { 40, 40 });

	P labelUp(Text("Up button ->"), style.gridStyle(1, 0), Style("color:red;"));
	P labelDown(Text("Down button ->"), style.gridStyle(1, 1));

	Button upButton("Up", ID("button_up"), style.gridStyle(2, 0),
		[&document](const ActionEvent& e) {
		std::cout << "Up Button Clicked" << std::endl;
		auto elem = document.getElementById("webi_content");
		elem.setInnerHTML("Value is Up");
	});
	Button downButton("Down", ID("button_down"), style.gridStyle(2, 1),
		[&document](const ActionEvent& e) {
		std::cout << "Down Button Clicked" << std::endl;
		auto elem = document.getElementById("webi_content");
		elem.setInnerHTML("Value is Down");
	})
	*/;

	auto doc = HTML(
		Header(
			WebiScript(),
			bootstrap::ViewPortTag(),
			bootstrap::CSSfromCDN()
		),
		Body(
			bootstrap::Nav(
				bootstrap::NavBarBrand("NavBar", Href("#")),
				bootstrap::NavToggleButton(),
				bootstrap::NavBar(
					bootstrap::NavItem(bootstrap::NavLink("Home", Href("#")), Classes("active")),
					bootstrap::NavDropdown("Dropdown", Href("#"),
						bootstrap::NavDropdownItem("Action 1", Href("#"), ID("bs-action-01"),
							EventListener("onclick",
								[](const ActionEvent& e) { std::cout << "Action 1 is clicked." << std::endl;}
							)
						),
						bootstrap::NavDropdownItem("Action 2", Href("#"), ID("bs-action-02"),
							EventListener("onclick",
								[](const ActionEvent& e) { std::cout << "Action 2 is clicked." << std::endl; }
							)
						),
						bootstrap::NavDropdownItem("Action 3", Href("#"), ID("bs-action-03"),
							EventListener("onclick",
								[](const ActionEvent& e) { std::cout << "Action 3 is clicked." << std::endl; }
							)
						)
					)
				)
			),
			bootstrap::ScriptsfromCDN()
		)
	);

	s->get("/", doc
	);


	std::cout << "Server is started." << std::endl;

	s->runBackground(8080, 8081);

	if (s->waitBackground()) { // wait forever.) 
		std::cout << "Background Server is ended." << std::endl;
	}
	else {
		std::cout << "Something happened." << std::endl;
	}

	return 0;
}
