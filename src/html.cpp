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

std::string Tag::toString() const {
  if (value_.length() > 0) return value_;
  std::string buf = "<" + name_;
  
  for(auto a : attrs_) {
    buf += " ";
    buf += a.toString();
  }
  
  buf += ">";
  
  for(auto c : children) {
    buf += c.toString();
  }
  
  buf += "</" + name_ + ">";
  return buf;
}

Text::Text(const std::string& value): Tag("") { value_ = value; }

Text::~Text() {}



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
  return "webi_on_button(" + button->getID() + ");";
}
