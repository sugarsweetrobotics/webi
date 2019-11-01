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


		inline Tag ViewPortTag() {
			return group(
				Tag("meta", Attribute("charset", "utf-8")),
				Tag("meta", { Attribute("name", "viewport"), Attribute("content", "width=device-width, initial-scale=1, shrink-to-fit=no") })
			);
		}

		class CSSfromCDN : public Tag {

		public:
			//<link rel = "stylesheet" href = "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" 
			// integrity = "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin = "anonymous">
			CSSfromCDN() : Tag("link", { Attribute("rel", "stylesheet"),
				Attribute("href", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"),
				Attribute("integrity", "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"),
				Attribute("crossorigin", "anonymous") }
			) {}
		};

		inline Tag ScriptsfromCDN() {
			return group(
				Tag("SCRIPT", { Attribute("src", "https://code.jquery.com/jquery-3.3.1.slim.min.js"),
					Attribute("integrity", "sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"),
					Attribute("crossorigin", "anonymous") }),
				Tag("SCRIPT", { Attribute("src", "https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"),
					Attribute("integrity", "sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"),
					Attribute("crossorigin", "anonymous") }),
				Tag("SCRIPT", { Attribute("src", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"),
					Attribute("integrity", "sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"),
					Attribute("crossorigin", "anonymous") }));
		}

		template<typename...R>
		Tag container(R...r) {
			return Tag("div", { className("container") }, r...);
		}

		template<typename...R>
		Tag gridRow(R...r) {
			return Tag("div", { className("row") }, r...);
		}

		template<typename...R>
		Tag gridColumn(R...r) {
			return Tag("div", { className("col-sm") }, r...);
		}

		template<typename...R>
		Tag nav(R...r) {
			return Tag("nav", { className("navbar navbar-expand-lg"), className("navbar-light"), className("bg-light") }, r...);
		}

		inline Tag navToggleButton() {
			return Tag("button", { className("navbar-toggler"),
				Attribute("type", "button"), Attribute("data-toggle", "collapse"),
				Attribute("data-target", "#navbarSupportedContent"), Attribute("aria-controls", "navbarSupportedContent"),
				Attribute("aria-expanded", "false"), Attribute("aria-label", "Toggle navigation") },
				Tag("span", className("navbar-toggler-icon"))
			);
		}

		template<typename...R>
		inline Tag navBarBrand(const std::string& title, R... r) {
			return Tag("a", { className("navbar-brand") }, text(title), r...);
		}

		template<typename...R>
		Tag navBar(R... r) {
			return Tag("DIV", { className("collapse navbar-collapse"),
				id("navbarSupportedContent") },
				Tag("ul", { className("navbar-nav mr-auto") }, r...));
		}

		template<typename...R>
		Tag navItem(R... r) {
			return Tag("li", { className("nav-item") }, r...);
		}

		template<typename...R>
		Tag navLink(const std::string& title, R...r) {
			return Tag("a", { className("nav-link") }, text(title), r...);
		}

		template<typename...R>
		Tag navDropdown(const std::string& caption, R...r) {
			return Tag("li", { className("nav-item", "dropdown") },
				Tag("a", { className("nav-link", "dropdown-toggle"), Attribute("role", "button"), Attribute("data-toggle", "dropdown"), Attribute("aria-haspopup", "true"), Attribute("aria-expanded", "false"), href("#") },
					text(caption)),
				Tag("div", { className("dropdown-menu"), Attribute("aria-labelledby", "navbarDropdown") }, r...));
		}
		
		template<typename...R>
		Tag navDropdownItem(const std::string& caption, R...r) { 
			return Tag("a", { className("dropdown-item") }, text(caption), r...);
		}


		inline Tag navDropdownDivider() {
			return Tag("div", { className("dropdown-divider") });
		}

		class Button : public Tag {
		public:
			inline const static auto Primary = Attribute("class", "btn-primary");
			inline const static auto Secondary = Attribute("class", "btn-secondary");

			inline const static auto Success = "btn-success";
			inline const static auto Danger = "btn-danger";
			inline const static auto Warning = "btn-warning";
			inline const static auto Info = "btn-info";

			inline const static auto Light = "btn-light";
			inline const static auto Dark = "btn-dark";

			inline const static auto Link = "btn-link";

			inline const static auto Small = "btn-sm";
			inline const static auto Large = "btn-lg";
		};

		template<typename...R>
		Tag button(const std::string& caption, R...r) {
			return Tag("button", Attribute("type", "button"), className("btn"), text(caption), r...);
		}

		template<typename...R>
		Tag card(R...r) {
			return div(className("card"), div(className("card-body"), r...));
		}

		template<typename...R>
		Tag cardTitle(const std::string& title, R...r) {
			return h5(className("card-title"), text(title),	r...);
		}

		template<typename...R>
		Tag cardSubtitle(const std::string& title, R...r) {
			return h6(className("card-subtitle", "mb-2"), text(title), r...);
		}

		template<typename...R>
		Tag cardText(const std::string& title, R...r) {
			return p(className("card-text"), text(title), r...);
		}

		class Modal : public Tag {
		public:
			template<typename... R>
			Modal(R...r) : Tag("div", className("modal", "fade"), 
				Tag("div", className("modal-dialog"), Attribute("role", "document"), 
					Tag("div", className("modal-content"), r...)))  {}
		};

		class ModalHeader : public Tag {
		public:
			template<typename... R>
			ModalHeader(R...r) : Tag("div", className("modal-header"), r...) {}
		};

		class ModalFooter : public Tag {
		public:
			template<typename... R>
			ModalFooter(R...r) : Tag("div", className("modal-footer"), r...) {}
		};

		class ModalTitle : public Tag {
		public:
			template<typename... R>
			ModalTitle(const std::string& title, R...r) : Tag("h5", className("modal-title"), text(title), r...) {}
		};

		class ModalBody : public Tag {
		public:
			template<typename... R>
			ModalBody(R...r) : Tag("div", className("modal-body"), r...) {}
		};
	};
};
