#include <iostream>

#include "webi/webi.h"
#include "webi_test.h"

using namespace webi;
using namespace webi::html;


int main(void) {
  webi::Webi webi;

  auto s = webi.createServer();
  auto document = s->createDocument();
  s->baseDirectory("../www");

  GridLayoutStyler gridStyle({20, 150, 30}, {40, 40});

  auto labelUp = p(text("Up button ->"), gridStyle.gridStyle(1, 0), style("color:red;"));
  auto labelDown = p(text("Down button ->"), gridStyle.gridStyle(1, 1));

  auto upButton = button("Up", id("button_up"), gridStyle.gridStyle(2, 0),
		  EventListener("onclick", [&document](const ActionEvent& e) {
		    std::cout << "Up Button Clicked" << std::endl;
		    auto elem = document.getElementById("webi_content");
		    elem.setInnerHTML("Value is Up");
		  }));
  auto downButton = button("Down", id("button_down"), gridStyle.gridStyle(2, 1),
		    EventListener("onclick", [&document](const ActionEvent& e) {
		      std::cout << "Down Button Clicked" << std::endl;
		      auto elem = document.getElementById("webi_content");
		      elem.setInnerHTML("Value is Down");
		    }));
  
  s->get("/", htmlDoc(
		   head(
			  WebiScript(), 
			  styleSheet("webi.css")),
		   body(
			WebiToolbar(),
			h1(text("This is Title")),
			p(id("webi_content"),
			  text("This is Test Page of Webi")
			  ),
			div(gridStyle.containerStyle(),
			    labelUp,upButton,
			    labelDown, downButton
			    )
			)
		   )
	 );


  std::cout << "Server is started." << std::endl;
  
  s->runBackground(8080, 8081);

  if (s->waitBackground()) { // wait forever.) 
    std::cout << "Background Server is ended." << std::endl;
  } else {
    std::cout << "Something happened." << std::endl;
  }
  
  return 0;
}
