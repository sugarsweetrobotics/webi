


#include "webi/remote_dom.h"





using namespace webi;



Document::Document(Server* ptr) : server_ptr_(ptr), body(this) {
  body._setTagName("body");
}



RemoteElement Document::getElementById(const std::string& id) {
  RemoteElement r(this);
  r.setId(id);
  return r;
}


RemoteElement::RemoteElement(Document *doc) : parent_(nullptr), doc_(doc) {}

RemoteElement& RemoteElement::setInnerHTML(const std::string& html) {
  if (id_) {
    document().server().elementCommandById(id_.value(), "set", "innerHTML", html);
  }
  return *this;
}


