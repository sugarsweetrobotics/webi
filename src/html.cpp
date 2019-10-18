#include <iostream>

#include "webi/html.h"

using namespace webi;

Attribute::Attribute(const std::string& key, const std::string& value): key_(key), value_(value) {
}

Attribute::~Attribute() {}

std::string Attribute::toString() const {
  return key_ + "=\"" + value_ + "\"";
}


Tag::Tag(const std::string& name) : name_(name) {}

Tag::Tag(const std::string& name, AttributeSet attrs): name_(name), attrs_(attrs) {}

Tag::~Tag() {}

// Join Multiple Attribute. This is mainly for styles declared separately.
static AttributeSet join(AttributeSet attrs) {
  std::vector<std::string> known_labels;
  AttributeSet return_values;
  for(auto a : attrs) {
    auto ret = std::find(known_labels.begin(), known_labels.end(), a.getKey());
    if (ret == known_labels.end()) {
      known_labels.push_back(a.getKey());
      return_values.push_back(a);
    } else {
      for(auto r : return_values) {
	if (r.getKey() == a.getKey()) {
	  std::swap(r, return_values.back());
	  return_values.pop_back();
	  r.setValue(r.getValue() + a.getValue());
	  return_values.push_back(r);
	}
      }
    }
  }
  return return_values;
}

std::string Tag::toString() const {
  if (value_.length() > 0) return value_;
  std::string buf = "<" + name_;

// Join Multiple Attribute. This is mainly for styles declared separately.
  auto attrs = join(attrs_); 
  for(auto a : attrs) {
    buf += " ";
    buf += a.toString();
  }
  buf += ">";
  
  for(auto c : children) {
    buf += c.toString();
  }
  
  buf += "</" + name_ + ">";

  std::cout << buf << std::endl;
  return buf;
}

Text::Text(const std::string& value): Tag("") { value_ = value; }

Text::~Text() {}

Button::Button(const std::string& caption, const ID& id, const Attribute& style,  EventCallback callback) : Button(caption, id, callback) {
  attrs_.push_back(style);
}

Button::Button(const std::string& caption, const ID& id, EventCallback callback) :
  Tag("input", id, Attribute("type", "button"), Attribute("value", caption)),
  id_(id.getValue())
{ 
  attrs_.push_back(Attribute("onclick", Button::generateOnClickedFunction(this)));
  eventListeners_.emplace("onclick", callback);
}

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

WebiToolbar::WebiToolbar():Tag("DIV", ID("webi-toolbar-box"), 
		      DIV(ID("webi-toolbar-msg"),
			  Text("This page is powered by Webi")),
		      DIV(ID("webi-toolbar-status"),
			  P(ID("webi-toolbar-status-off"), Text("Not Connected")),
			  P(ID("webi-toolbar-status-on"), Text("Connected")))
			       ) {
}

