#pragma once

#include <string>
#include <vector>

#include "xml.h"


namespace webi {

	/**
	 *
	 */
	class ID : public Attribute {
	public:
		ID(const std::string& value) : Attribute("id", value) {}
		virtual ~ID() {}
	};

	/**
	 *
	 */
	class Classes : public Attribute {
	private:
		std::string concatClass(const std::string& s) {
			return s;
		}

		template<typename... R>
		std::string concatClass(const std::string& s, R... r) {
			return s + " " + concatClass(r...);
		}

	public:
		template<typename... R>
		Classes(R... r) : Attribute("class", concatClass(r...)) {}

		Classes(const std::string& value) : Attribute("class", value) {}
		virtual ~Classes() {}
	};

	/**
	 *
	 */
	class Style : public Attribute {
	public:
		Style(const std::string& value) : Attribute("style", value) {}
		virtual ~Style() {}
	};

	/**
	 *
	 */
	class H1 : public Tag {
	public:
		H1() : Tag("H1") {}

		template<typename T, typename...R>
		H1(const T& t, R... r) : Tag("H1", t, r...) {}
		virtual ~H1() {}
	};

	class DIV : public Tag {
	public:
		DIV() : Tag("DIV") {}
		template<typename T, typename...R>
		DIV(const T& t, R... r) : Tag("DIV", t, r...) {}
		virtual ~DIV() {}
	};

	/**
	 *
	 */
	class P : public Tag {
	public:
		P() : Tag("P") {}

		template<typename T, typename...R>
		P(const T& t, R... r) : Tag("P", t, r...) {}
		virtual ~P() {}
	};

	/**
	 *
	 */
	class HTML : public Tag {
	public:
		HTML() : Tag("HTML") {}

		template<typename T, typename...R>
		HTML(const T& t, R... r) : Tag("HTML", t, r...) {}
		virtual ~HTML() {}
	};

	/**
	 *
	 */
	class Header : public Tag {
	public:
		Header() : Tag("HEAD") {}

		template<typename T, typename...R>
		Header(const T& t, R... r) : Tag("HEAD", t, r...) {}
		virtual ~Header() {}
	};

	/**
	 *
	 */
	class Title : public Tag {
	public:
		Title(const std::string& title) : Tag("TITLE", Text(title)) {}
	};


	/**
	 *
	 */
	class Body : public Tag {
	public:
		Body() : Tag("BODY") {}

		template<typename T, typename...R>
		Body(const T& t, R... r) : Tag("BODY", t, r...) {}
		virtual ~Body() {}
	};

	/**
	 *
	 */
	class StyleSheet : public Tag {
	private:
	public:
		StyleSheet(const std::string& ref) : Tag("LINK", Attribute("rel", "stylesheet"),
			Attribute("type", "text/css"),
			Attribute("href", ref)) {}
		virtual ~StyleSheet() {}
	};

	/**
	 *
	 */
	class Button : public Tag {
	private:
		std::string id_;

	public:
		std::string getID() const { return id_; }
	public:

		//Button(const std::string& caption, const ID& id, EventCallback callback);

		
		template<typename...R>
		Button(const std::string& caption, const ID& id, R...r) : Tag("input", id,
			Attribute("type", "button"), Attribute("value", caption), r...),
			id_(id.getValue()) {}
		
//		Button(const std::string& caption, const ID& id, const Attribute& style, EventCallback callback);
		virtual ~Button();

	public:
		virtual std::string toString() const override;

	public:
		static std::string generateOnClickedFunction(const Button* button);
	};

	/**
	 *
	 */
	class WebiScript : public Tag {
	public:
		WebiScript() : Tag("SCRIPT", Attribute("type", "text/javascript"),
			Attribute("src", "webi.js")) {}
		virtual ~WebiScript() {}

		static std::string generateWebiScript();
	};


	class WebiToolbar : public Tag {
	public:
		WebiToolbar();
		virtual ~WebiToolbar() {}
	};


	class Href : public Attribute {
	public:
		template<typename...R>
		Href(const std::string& link, R... r) : Attribute("href", link, r...) {}
	};
};
