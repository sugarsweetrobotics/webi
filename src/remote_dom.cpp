
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

const RemoteElement& RemoteElement::set(const std::string& key, const std::string& value) const {
	if (id_) {
		document().server().elementCommandById(id_.value(), "set", key, value);
	}
	return *this;
}

const RemoteElement& RemoteElement::get(const std::string& key, std::function<void(const ElementResponse&)> callback) const {
	if (id_) {
		document().server().elementResponseById(id_.value(), callback);
		document().server().elementCommandById(id_.value(), "get", key, "");
	}
	return *this;
}
