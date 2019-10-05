#include "webi/webi.h"

const char* content = "<HTML>"
"<HEADER>"
"<link rel='stylesheet' type='text/css' href='webi.css'>"
"</HEADER>"
"<BODY>"
"Hoooooo Yahhhh"
"<BODY>"
"</HTML>";

using namespace webi;

int main(void) {
  webi::Webi webi;


  auto s = webi.createServer();

  s->baseDirectory("./www");

  //  s->getHTML("/", content);

  s->getHTML("/", HTML(
		      Header(
			     WebiScript(), 
			     StyleSheet("webi.css")),
		      Body(
			   Style("font-size: 5pt;"),
			   Text("Hello World"),
			   Button("Hello"))));

  s->runForever(8080);
  
  return 0;
}
