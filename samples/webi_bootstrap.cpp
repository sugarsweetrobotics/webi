#include <iostream>

#include "webi/webi.h"
#include "webi/bootstrap.h"

using namespace webi;

namespace bs = webi::bootstrap;

int main(void) {
	webi::Webi webi;


	auto s = webi.createServer();
	//auto document = s->createDocument();
	s->baseDirectory("../www");

	auto navbar = bs::nav(
		bs::navBarBrand("NavBar", href("#")),
		bs::navToggleButton(),
		bs::navBar(
			bs::navItem(bs::navLink("Home", href("#")), className("active")),
			bs::navDropdown("Dropdown", href("#"),
				bs::navDropdownItem("Action 1", href("#"), id("bs-action-01"),
					EventListener("onclick",
						[](const ActionEvent& e) { std::cout << "Action 1 is clicked." << std::endl; }
					)
				),
				bs::navDropdownItem("Action 2", href("#"), id("bs-action-02"),
					EventListener("onclick",
						[](const ActionEvent& e) { std::cout << "Action 2 is clicked." << std::endl; }
					)
				),
				bs::navDropdownItem("Action 3", href("#"), id("bs-action-03"),
					EventListener("onclick",
						[](const ActionEvent& e) { std::cout << "Action 3 is clicked." << std::endl; }
					)
				)
			)
		)
	);

	auto doc = html(
		head(
			WebiScript(),
			bs::ViewPortTag(),
			bs::CSS()
		),
		body(
			navbar,
			bs::container(
				bs::gridRow(
					bs::gridColumn(
						bs::card(
							bs::cardTitle("Card Title"),
							bs::cardSubtitle("Card SubTitle"),
							bs::cardText("Webi says Hello Bootstrap. The world is beutiful"),
							bs::button("Primary Button", bs::Button::Primary),
							bs::button("Secondary Button", bs::Button::Secondary)
						)
					), 
					bs::gridColumn(
						bs::card(
							bs::cardTitle("Card Title"),
							bs::cardSubtitle("Card SubTitle"),
							bs::cardText("Webi says Hello Bootstrap. The world is beutiful")
						)
					)
				)
			),
			

			bs::Scripts()
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
