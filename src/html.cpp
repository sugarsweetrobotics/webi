#include <iostream>

#include "webi/html.h"

using namespace webi;

Button::~Button() {}

std::string Button::toString() const {
	return Tag::toString();
}

std::string webi::WebiScript::generateWebiScript() {
	return "function webi_on_button(e) { alert('Hello Webi'); };";
}

std::string webi::Button::generateOnClickedFunction(const Button* button) {
	return "webi.on_button('" + button->getID() + "');";
}

WebiToolbar::WebiToolbar() :Tag("DIV", ID("webi-toolbar-box"),
	DIV(ID("webi-toolbar-msg"),
		Text("This page is powered by Webi")),
	DIV(ID("webi-toolbar-status"),
		P(ID("webi-toolbar-status-off"), Text("Not Connected")),
		P(ID("webi-toolbar-status-on"), Text("Connected")))
) {
}

