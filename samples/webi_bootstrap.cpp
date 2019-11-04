#include <iostream>

#include "webi/webi.h"
#include "webi/bootstrap.h"

using namespace webi;

using namespace webi::html;

namespace bs = webi::bootstrap;

int main(void) {
	std::cout << "webi_bootstrap" << std::endl;
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
					onclick([](auto e) { std::cout << "Action 1 is clicked." << std::endl; })
				),
				bs::navDropdownItem("Action 2", href("#"), id("bs-action-02"),
					onclick([](auto e) { std::cout << "Action 2 is clicked." << std::endl; })
				),
				bs::navDropdownItem("Action 3", href("#"), id("bs-action-03"),
					onclick([](auto e) { std::cout << "Action 3 is clicked." << std::endl; })
				)
			)
		)
	);

	auto modal = bs::modal(id("my-modal"),
		bs::modalHeader(bs::modalTitle("Modal Title"),
			bs::modalCloseButton()
		),
		bs::modalBody(text("This is My Modal.")),
		bs::modalFooter(
			bs::button("Cancel", bs::modalDismiss(), id("modal-close-button"),
				onclick([](auto e) {std::cout << "Modal CancelButton is Clicked" << std::endl;})
			),
			bs::button("OK", id("modal-ok-button"), bs::modalClose("my-modal"),
				onclick([](auto e) {std::cout << "Modal OK Button is Clicked" << std::endl;})
			)
		)
	);

	auto doc = htmlDoc(
		head(
			link(rel("stylesheet"), href("webi.css")),
			webi::webiScript(),
			bs::ViewPortTag(),
			bs::CSS()
		),
		body(
			modal, /// modal must be inclided in HTML.
			navbar,

			h2(text("Card And Buttons Example")),

			bs::container(
				bs::gridRow(
					bs::gridColumn(
						bs::card(
							bs::cardTitle("Card Title"),
							bs::cardSubtitle("Card SubTitle"),
							bs::cardText("Webi says Hello Bootstrap. The world is beutiful"),
							bs::button("Primary Btn", bs::Button::Primary, style("margin-right:5px;")),
							bs::button("Secondary Btn", bs::Button::Secondary)
						)
					),
					bs::gridColumn(
						bs::card(
							bs::cardTitle("Card Title"),
							bs::cardSubtitle("Card SubTitle"),
							bs::cardText("Webi says Hello Bootstrap. The world is beutiful"),
							bs::button("Primary Btn", bs::Button::Primary, style("margin-right:5px;")),
							bs::button("Secondary Btn", bs::Button::Secondary)
						)
					)
				)
			),

			h2(text("Modal Example")),
			bs::container(
				bs::button("Open Modal", bs::Button::Primary, bs::modalOpen("my-modal"))
			),

			h2(text("Slider Example")),
			bs::container(
				bs::gridRow(
					html::p(text("Volume 1"), style("margin-right:20px;")),
					bs::slider("volume1", 0, 100, 1, 50, 
						bs::onslide([](auto e) {std::cout << "onSlide Volume 1 (" << e.value << ")" << std::endl;})
					)
				),
				bs::gridRow(
					html::p(text("Volume 2"), style("margin-right:20px;")),
					bs::slider("volume2", 0, 100, 1, 50, 
						bs::onslide([](auto e) {std::cout << "onSlide Volume 2 (" << e.value << ")" << std::endl;})
					)
				)
			),

			bs::Scripts()
		)
	);

	s->get("/", doc);


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
