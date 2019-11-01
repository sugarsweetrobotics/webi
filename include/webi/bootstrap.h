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

		inline Tag CSSfromCDN() {
			return group(
				link(rel("stylesheet"),
					href("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"),
					Attribute("integrity", "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"),
					Attribute("crossorigin", "anonymous")),
				link(rel("stylesheet"),
					href("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.6.2/css/bootstrap-slider.css"),
					Attribute("integrity", "sha384-FJdXLlAY9riDg/a7UYHICzoCBmHSGaCIB8tsRSryjMcg+BfyuZlyWvRlx8m6Ntfh"),
					Attribute("crossorigin", "anonymous"))
			);
		}

		inline Tag CSS() {
			return group(
				link(rel("stylesheet"),
					href("bootstrap-4.3.1/css/bootstrap.min.css")),
				link(rel("stylesheet"),
					href("bootstrap-slider-10.6.2/css/bootstrap-slider.css"))
				);
		}

		inline Tag ScriptsfromCDN() {
			return group(
				script(src("https://code.jquery.com/jquery-3.3.1.slim.min.js"),
					Attribute("integrity", "sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"),
					Attribute("crossorigin", "anonymous")),
				script(src("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"),
					Attribute("integrity", "sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"),
					Attribute("crossorigin", "anonymous")),
				script(src("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"),
					Attribute("integrity", "sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"),
					Attribute("crossorigin", "anonymous")),
				script(src("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.6.2/bootstrap-slider.min.js"),
					Attribute("integrity", "sha384-GeRVXaaRfDlGPnvQ2jvqMPvvcWsUQ5il0aXJ4g5b0jXB18yOrR6MEVxVOJKHch4j"),
					Attribute("crossorigin", "anonymous")));
			}


		inline Tag Scripts() {
			return group(
				script(src("jquery-3.3.1/jquery.slim.min.js")),
				script(src("popper.js-1.14.7/umd/popper.min.js")),
				script(src("bootstrap-4.3.1/js/bootstrap.min.js")),
				script(src("bootstrap-slider-10.6.2/bootstrap-slider.min.js"))
			);
		}

		template<typename...R>
		Tag container(R...r) {
			return div(className("container"), r...);
		}

		template<typename...R>
		Tag gridRow(R...r) {
			return div(className("row"), r...);
		}

		template<typename...R>
		Tag gridColumn(R...r) {
			return div(className("col-sm"), r...);
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
			return div(className("collapse navbar-collapse"),
				id("navbarSupportedContent"),
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
				div(className("dropdown-menu"), Attribute("aria-labelledby", "navbarDropdown"), r...));
		}
		
		template<typename...R>
		Tag navDropdownItem(const std::string& caption, R...r) { 
			return Tag("a", { className("dropdown-item") }, text(caption), r...);
		}

		inline Tag navDropdownDivider() {
			return div(className("dropdown-divider"));
		}

		class Button : public Tag {
		public:
			inline const static auto Primary = Attribute("class", "btn-primary");
			inline const static auto Secondary = Attribute("class", "btn-secondary");

			inline const static auto Success = Attribute("class", "btn-success");
			inline const static auto Danger = Attribute("class", "btn-danger");
			inline const static auto Warning = Attribute("class", "btn-warning");
			inline const static auto Info = Attribute("class", "btn-info");

			inline const static auto Light = Attribute("class", "btn-light");
			inline const static auto Dark = Attribute("class", "btn-dark");

			inline const static auto Link = Attribute("class", "btn-link");

			inline const static auto Small = Attribute("class", "btn-sm");
			inline const static auto Large = Attribute("class", "btn-lg");
		};

		template<typename...R>
		Tag button(const std::string& caption, const Attribute& _id, R...r) {
			return Tag("button", 
				Attribute("type", "button"), className("btn"),
				text(caption), 
				_id,
				Attribute("onclick", "webi.on_action_event('input', 'button', 'onclick', '" + _id.getValue() + "')"),
				r...);
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

		template<typename... R>
		Tag modal(const Attribute& id_, R...r) {
			return div(className("modal", "fade"), id_,
				Attribute("tabindex", "-1"),
				Attribute("role", "dialog"),
				Attribute("aria-labelledby", "exampleModalLongTitle"),
				Attribute("aria-hidden", "true"),
					div(className("modal-dialog"), 
						Attribute("role", "document"),
					div(className("modal-content"), r...))
			);
		}

		template<typename... R>
		Tag modalHeader(R...r) {
			return div(className("modal-header"), r...);
		}

		template<typename... R>
		Tag modalFooter(R...r) {
			return div(className("modal-footer"), r...);
		}


		template<typename... R>
		Tag modalTitle(const std::string& title, R...r) {
			return h5(className("modal-title"), text(title), r...);
		}

		template<typename... R>
		Tag modalBody(R...r) {
			return div(className("modal-body"), r...);
		}

		inline AttributeSet modalToggle(const std::string& targetId) {
			return AttributeSet({ Attribute("data-toggle", "modal"),
				Attribute("data-target", "#"+targetId) });
		}

		inline AttributeSet modalOpen(const std::string& targetId) {
			return AttributeSet({ Attribute("data-toggle", "modal"),
				Attribute("data-target", "#" + targetId) });
		}

		inline AttributeSet modalClose(const std::string& targetId) {
			return AttributeSet({ Attribute("data-toggle", "modal"),
				Attribute("data-target", "#" + targetId) });
		}


		inline Attribute modalDismiss() {
			return Attribute("data-dismiss", "modal");
		}

		template<typename...R>
		inline Tag modalCloseButton(R...r) {
			return  Tag("button", Attribute("type", "button"), className("close"), Attribute("data-dismiss", "modal"),
				Attribute("aria-label", "Close"),
				Tag("span", Attribute("aria-hidden", "true"), text("&times;")),
				r...);
		}

		///---------------------- Slider ----------------------

		template<typename...R>
		Tag slider(const std::string& idStr, int min, int max, int step, int value, R...r) {
			return Tag("input", id(idStr), 
				Attribute("type", "text"),
				Attribute("data-slider-id", idStr + "Slider"),
				Attribute("data-slider-min", std::to_string(min)),
				Attribute("data-slider-max", std::to_string(max)),
				Attribute("data-slider-step", std::to_string(step)),
				Attribute("data-slider-value", std::to_string(value)),
				InitializerScript("$(\"#" + idStr + "\").slider().on(\"slide\", (e)=>{webi.on_action_event(\"slider\", \"text\", \"slide\", \"" + idStr + "\", e.value);});"),
				r...);
		}


		inline EventListener onslide(EventCallback cb) {
			return event("slide", cb);
		}

	};
};
