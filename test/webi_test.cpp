#include "webi/webi.h"

using namespace webi;

int main(void) {
  webi::Webi webi;


  auto s = webi.createServer();

  s->baseDirectory("../www");

  s->getHTML("/", HTML(
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
			   Button("Hello"))));

  s->response("/webi_button_0", "POST", "application/json", [](const Request& r) {
      return Response(200, "Hello:json");
    });

  s->runForever(8080);
  
  return 0;
}
