#include <iostream>

#include "webi/xml.h"

using namespace webi;

Attribute::Attribute(const std::string& key, const std::string& value) : key_(key), value_(value) {
}

Attribute::Attribute(const std::string& key, std::function<std::string()> cb) : key_(key), value_(""), value_callback_(cb) {
}

Attribute::~Attribute() {}

std::string Attribute::toString() const {
	return getKey() + "=\"" + getValue() + "\"";
}

Tag::Tag() : name_("") {}

Tag::Tag(const std::string& name) : name_(name) {}

Tag::Tag(const std::string& name, const TagSet& tags) : name_(name), children(tags) {}

Tag::Tag(const std::string& name, const AttributeSet& attrs) : name_(name), attrs_(attrs) {}

Tag::Tag(const std::string& name, const AttributeSet& attrs, const TagSet& tags) : name_(name), attrs_(attrs), children(tags) {}


Tag::~Tag() {}

// Join Multiple Attribute. This is mainly for styles declared separately.
static AttributeSet join(AttributeSet attrs) {
	std::vector<std::string> known_labels;
	AttributeSet return_values;
	for (auto a : attrs) {
		auto ret = std::find(known_labels.begin(), known_labels.end(), a.getKey());
		if (ret == known_labels.end()) {
			known_labels.push_back(a.getKey());
			return_values.push_back(a);
		}
		else {
			for (int i = 0; i < return_values.size();i++) {// : return_values) {
				auto r = return_values[i];
				if (r.getKey() == a.getKey()) {
					return_values.erase(return_values.begin() + i);
					r.setValue(r.getValue() + " " + a.getValue()); // Need Brank for Classes
					return_values.push_back(r);
				}
			}
		}
	}
	return return_values;
}

std::string Tag::toString() const {
	if (value_.length() > 0) return value_;

	std::string buf;
	if (name_ != "GROUP") {
		buf = "<" + name_;

		// Join Multiple Attribute. This is mainly for styles declared separately.
		auto attrs = join(attrs_);
		for (auto a : attrs) {
			buf += " ";
			buf += a.toString();
		}
		buf += ">";
	}

	for (auto c : children) {
		buf += c.toString();
	}

	if (name_ != "GROUP") {
		buf += "</" + name_ + ">";
	}
	return buf;
}
