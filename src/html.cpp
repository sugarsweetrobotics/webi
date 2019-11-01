#include <iostream>

#include "webi/html.h"

using namespace webi;


WebiToolbar::WebiToolbar() :Tag("DIV", id("webi-toolbar-box"),
	div(id("webi-toolbar-msg"),
		text("This page is powered by Webi")),
	div(id("webi-toolbar-status"),
		p(id("webi-toolbar-status-off"), text("Not Connected")),
		p(id("webi-toolbar-status-on"), text("Connected")))
) {
}

