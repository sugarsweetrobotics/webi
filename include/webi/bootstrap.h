#pragma once

#include <string>
#include <vector>
#include <map>

#include <optional>
#include <functional>
#include "webi/webi_common.h"

#include "xml.h"
#include "html.h"

namespace webi {

	namespace bootstrap {
		class ViewPortTag : public Group {

		public:
			//<meta charset="utf-8">
			//<meta name = "viewport" content = "width=device-width, initial-scale=1, shrink-to-fit=no">
			ViewPortTag() : Group(
				Tag("meta", Attribute("charset", "utf-8")),
				Tag("meta", Attribute("name", "viewport"), Attribute("content", "width=device-width, initial-scale=1, shrink-to-fit=no"))
			) {}
		};


		class CSSfromCDN : public Tag {

		public:
			//<link rel = "stylesheet" href = "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" 
			// integrity = "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin = "anonymous">
			CSSfromCDN() : Tag("link", Attribute("rel", "stylesheet"), 
				Attribute("href", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"), 
				Attribute("integrity", "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"),
				Attribute("crossorigin", "anonymous")
			) {}
		};

		class ScriptsfromCDN : public Group {
		public:
			// <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
			//<script src = "https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity = "sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin = "anonymous">< / script>
			//<script src = "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity = "sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin = "anonymous">< / script>

			ScriptsfromCDN() : Group(
				Tag("SCRIPT", Attribute("src", "https://code.jquery.com/jquery-3.3.1.slim.min.js"),
					Attribute("integrity", "sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"),
					Attribute("crossorigin", "anonymous")),
				Tag("SCRIPT", Attribute("src", "https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"),
					Attribute("integrity", "sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"),
					Attribute("crossorigin", "anonymous")),
				Tag("SCRIPT", Attribute("src", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"),
					Attribute("integrity", "sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"),
					Attribute("crossorigin", "anonymous"))) {}
		};

		class Nav : public Tag {

		public:
			template<typename...R>
			Nav(R...r) : Tag("nav", Classes("navbar navbar-expand-lg"),
				Classes("navbar-light"), Classes("bg-light"), r...) {}
		};

		class NavToggleButton : public Tag {
		public:
			NavToggleButton() : Tag("button", Classes("navbar-toggler"),
				Attribute("type", "button"), Attribute("data-toggle", "collapse"),
				Attribute("data-target", "#navbarSupportedContent"), Attribute("aria-controls", "navbarSupportedContent"),
				Attribute("aria-expanded", "false"), Attribute("aria-label", "Toggle navigation"),
				Tag("span", Classes("navbar-toggler-icon"))
			) {}

		};

		class NavBarBrand : public Tag {
		public:
			// <a class = "navbar-brand" href = "#">Navbar< / a>
			template<typename...R>
			NavBarBrand(const std::string& title, R... r) : Tag("a", Classes("navbar-brand"), Text(title), r...) {}
		};

		/**
		 *
		 */
		class NavBar : public Tag {
		public:
			template<typename...R>
			NavBar(R... r) : Tag("DIV", Classes("collapse navbar-collapse"), 
				ID("navbarSupportedContent"), 
				Tag("ul", Classes("navbar-nav mr-auto"), r...)) {}
		};

		class NavItem : public Tag {
		public:
			template<typename...R>
			NavItem(R... r) : Tag("li", Classes("nav-item"), r...) {}
		};

		class NavLink : public Tag {
		public:
			template<typename...R>
			NavLink(const std::string& title, R...r) : Tag("a", Text(title), Classes("nav-link"), r...) {}
		};

		//<li class = "nav-item dropdown">
		//	<a class = "nav-link dropdown-toggle" href = "#" id = "navbarDropdown" role = "button" data - toggle = "dropdown" aria - haspopup = "true" aria - expanded = "false">
		//	Dropdown
		//	< / a>
		class NavDropdown : public Tag {
		public:
			template<typename...R>
			NavDropdown(const std::string& caption, R...r) : Tag("li", Classes("nav-item", "dropdown"),
				Tag("a", Classes("nav-link", "dropdown-toggle"), Attribute("role", "button"), Attribute("data-toggle", "dropdown"), Attribute("aria-haspopup", "true"), Attribute("aria-expanded", "false"),
					Text(caption)), 
				Tag("div", Classes("dropdown-menu"), Attribute("aria-labelledby", "navbarDropdown"), r...)) {}

		};

		class NavDropdownItem : public Tag {
		public:
			template<typename...R>
			NavDropdownItem(const std::string& caption, R...r) : Tag("a", Classes("dropdown-item"), Text(caption), r...) {
			}
		};

		class NavDropdownDivider : public Tag {
		public:
			NavDropdownDivider() : Tag("div", Classes("dropdown-divider")) {}
		};
	};
};
