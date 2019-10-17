#include <iostream>

#include "webi/webi.h"
#include "webi_test.h"

using namespace webi;

int main(void) {
  webi::Webi webi;


  auto s = webi.createServer();
  auto ws = webi.createWebSocketServer();

  s->baseDirectory("../www");

  s->get("/", HTML(
		   Header(
			  WebiScript(), 
			  StyleSheet("webi.css")),
		   Body(
			H1(
			   Text("Hello World")
			   ),
			P(
			  Classes("content", "content-new"),
			  Text("This is Test Page of Webi")
			  ),
			Button("Hello", ID("webi_test"), [](const ActionEvent& e) {
			    std::cout << "Button Clicked" << std::endl;
			  })
			)
		   )
	 );
  
  s->response("/webi_button_0", "PUT", "application/json", [](const Request& r) {
      return Response(200, "{Hello:json}");
    });
  s->response("/webi_button_0", "POST", "application/json", [](const Request& r) {
      return Response(200, "{Hello:json}");
    });

  //s->runForever(8080);

  std::cout << "Server is started." << std::endl;
  
  ws->runBackground(8081);

  s->runBackground(8080);
  //  s->runForever(8088);

  if (s->waitBackground()) { // wait forever.) 
    std::cout << "Background Server is ended." << std::endl;
  } else {
    std::cout << "Something happened." << std::endl;
  }
  
  return 0;
}
