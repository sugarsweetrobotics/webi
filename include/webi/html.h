 #pragma once

#include <string>
#include <vector>

#include "xml.h"


namespace webi::html {

	using Attribute = xml::Attribute;

	using EventListener = xml::EventListener;

	using EventCallback = xml::EventCallback;

	using InitializerScript = xml::InitializerScript;

	using ActionEvent = xml::ActionEvent;

	using Tag = xml::Tag;

	inline auto event = xml::event;

	inline auto text = xml::text;

	

	inline Attribute id(const std::string& value) {
		return Attribute("id", value);
	}

	inline std::string concatClass(const std::string& s) {
		return s;
	}

	template<typename... R>
	std::string concatClass(const std::string& s, R... r) {
		return s + " " + concatClass(r...);
	}

	template<typename... R>
	Attribute className(R... r) {
		return Attribute("class", concatClass(r...));
	}

	inline Attribute style(const std::string& value) {
		return Attribute("style", value);
	}

	template<typename... R>
	Tag script(R...r) {
		return Tag("SCRIPT", r...);
	}

	inline Attribute src(const std::string& value) {
		return Attribute("src", value);
	}

	template<typename...R>
	Tag link(R...r) {
		return Tag("link", r...);
	}

	inline Attribute rel(const std::string& value) {
		return Attribute("rel", value);
	}


	inline Attribute scriptType(const std::string& type) {
		return Attribute("type", type);
	}


	template<typename T, typename...R>
	Tag h1(const T& t, R... r) {
		return Tag("H1", t, r...);
	}

	template<typename T, typename...R>
	Tag h2(const T& t, R... r) {
		return Tag("H2", t, r...);
	}

	template<typename T, typename...R>
	Tag h3(const T& t, R... r) {
		return Tag("H3", t, r...);
	}

	template<typename T, typename...R>
	Tag h4(const T& t, R... r) {
		return Tag("H4", t, r...);
	}

	template<typename...R>
	Tag h5(R... r) {
		return Tag("H5", r...);
	}

	template<typename T, typename...R>
	Tag h6(const T& t, R... r) {
		return Tag("H6", t, r...);
	}


	template<typename...R>
	Tag div(R... r) {
		return Tag("DIV", r...);
	};

	template<typename...R>
	Tag p(R... r) { 
		return Tag("P", r...);
	};

	template<typename...R>
	Tag htmlDoc(R... r) {
		return Tag("HTML", r...);
	}

	template<typename...R>
	Tag head(R... r) {
		return Tag("HEAD", r...);
	}

	inline Tag title(const std::string& title) { 
		return Tag("TITLE", text(title));
	};

	template<typename...R>
	Tag body(R... r) {
		return Tag("BODY", r...);
	}

	inline Tag styleSheet(const std::string& ref) {
		return Tag("LINK", { Attribute("rel", "stylesheet"),
			Attribute("type", "text/css"),
			Attribute("href", ref) });
	}

	template<typename...R>
	Tag input(const std::string& caption, const std::string& type, const Attribute& _id, R...r) {
		return Tag("input", { _id,
			Attribute("type", type), Attribute("value", caption) }, r...);
	}

	template<typename...R>
	Tag button(const std::string& caption, const Attribute& _id, R...r) {
		return input(caption, "button", _id, 
			//Attribute("onclick", "webi.on_action_event('input', 'button', 'onclick', '" + _id.getValue()+ "')"),
			r...);
	}

	template<typename...R>
	Tag textBox(const std::string& caption, const Attribute& id, R...r) {
		return input(caption, "text", id, r...);
	}

	inline EventListener onclick(EventCallback cb) {
		return event("click", cb);
	}

	/**
	 *
	 */
	inline Tag WebiScript() {
		return script(scriptType("text/javascript"), src("webi.js"));
	}


	class WebiToolbar : public Tag {
	public:
		WebiToolbar();
		virtual ~WebiToolbar() {}
	};

	template<typename...R>
	Attribute href(const std::string& link, R... r) {
		return Attribute("href", link, r...);
	}
};
