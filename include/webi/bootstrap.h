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

	
		inline webi::html::Tag ViewPortTag() {
			return group(
				webi::html::Tag("meta", webi::html::Attribute("charset", "utf-8")),
				webi::html::Tag("meta", { webi::html::Attribute("name", "viewport"), 
				webi::html::Attribute("content", "width=device-width, initial-scale=1, shrink-to-fit=no") })
			);
		}

		inline webi::html::Tag CSSfromCDN() {
			return webi::xml::group(
				webi::html::link(webi::html::rel("stylesheet"),
					webi::html::href("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"),
					webi::html::Attribute("integrity", "sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"),
					webi::html::Attribute("crossorigin", "anonymous")),
				webi::html::link(webi::html::rel("stylesheet"),
					webi::html::href("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.6.2/css/bootstrap-slider.css"),
					webi::html::Attribute("integrity", "sha384-FJdXLlAY9riDg/a7UYHICzoCBmHSGaCIB8tsRSryjMcg+BfyuZlyWvRlx8m6Ntfh"),
					webi::html::Attribute("crossorigin", "anonymous"))
			);
		}

		inline webi::html::Tag CSS() {
			return webi::xml::group(
				webi::html::link(webi::html::rel("stylesheet"),
					webi::html::href("bootstrap-4.3.1/css/bootstrap.min.css")),
				webi::html::link(webi::html::rel("stylesheet"),
					webi::html::href("bootstrap-slider-10.6.2/css/bootstrap-slider.css"))
				);
		}

		inline webi::html::Tag ScriptsfromCDN() {
			return webi::xml::group(
				webi::html::script(webi::html::src("https://code.jquery.com/jquery-3.3.1.slim.min.js"),
					webi::html::Attribute("integrity", "sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"),
					webi::html::Attribute("crossorigin", "anonymous")),
				webi::html::script(webi::html::src("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js"),
					webi::html::Attribute("integrity", "sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"),
					webi::html::Attribute("crossorigin", "anonymous")),
				webi::html::script(webi::html::src("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"),
					webi::html::Attribute("integrity", "sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"),
					webi::html::Attribute("crossorigin", "anonymous")),
				webi::html::script(webi::html::src("https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.6.2/bootstrap-slider.min.js"),
					webi::html::Attribute("integrity", "sha384-GeRVXaaRfDlGPnvQ2jvqMPvvcWsUQ5il0aXJ4g5b0jXB18yOrR6MEVxVOJKHch4j"),
					webi::html::Attribute("crossorigin", "anonymous")));
			}


		inline webi::html::Tag Scripts() {
			return xml::group(
				html::script(html::src("jquery-3.3.1/jquery.slim.min.js")),
				html::script(html::src("popper.js-1.14.7/umd/popper.min.js")),
				html::script(html::src("bootstrap-4.3.1/js/bootstrap.min.js")),
				html::script(html::src("bootstrap-slider-10.6.2/bootstrap-slider.min.js"))
			);
		}

		template<typename...R>
		webi::html::Tag container(R...r) {
			return html::div(html::className("container"), r...);
		}

		template<typename...R>
		webi::html::Tag gridRow(R...r) {
			return html::div(html::className("row"), r...);
		}

		template<typename...R>
		webi::html::Tag gridColumn(R...r) {
			return html::div(html::className("col-sm"), r...);
		}

		template<typename...R>
		webi::html::Tag nav(R...r) {
			return html::Tag("nav", { html::className("navbar navbar-expand-lg"), html::className("navbar-light"), html::className("bg-light") }, r...);
		}

		inline html::Tag navToggleButton() {
			return html::Tag("button", { html::className("navbar-toggler"),
				html::Attribute("type", "button"), html::Attribute("data-toggle", "collapse"),
				html::Attribute("data-target", "#navbarSupportedContent"), html::Attribute("aria-controls", "navbarSupportedContent"),
				html::Attribute("aria-expanded", "false"), html::Attribute("aria-label", "Toggle navigation") },
				html::Tag("span", html::className("navbar-toggler-icon"))
			);
		}

		template<typename...R>
		inline webi::html::Tag navBarBrand(const std::string& title, R... r) {
			return webi::html::Tag("a", { html::className("navbar-brand") }, html::text(title), r...);
		}

		template<typename...R>
		webi::html::Tag navBar(R... r) {
			return html::div(html::className("collapse navbar-collapse"),
				html::id("navbarSupportedContent"),
				webi::html::Tag("ul", { html::className("navbar-nav mr-auto") }, r...));
		}

		template<typename...R>
		webi::html::Tag navItem(R... r) {
			return html::Tag("li", { html::className("nav-item") }, r...);
		}

		template<typename...R>
		webi::html::Tag navLink(const std::string& title, R...r) {
			return webi::html::Tag("a", { html::className("nav-link") }, html::text(title), r...);
		}

		template<typename...R>
		webi::html::Tag navDropdown(const std::string& caption, R...r) {
			return webi::html::Tag("li", { html::className("nav-item", "dropdown") },
				webi::html::Tag("a", { html::className("nav-link", "dropdown-toggle"), html::Attribute("role", "button"), 
				html::Attribute("data-toggle", "dropdown"), html::Attribute("aria-haspopup", "true"), html::Attribute("aria-expanded", "false"), html::href("#") },
					html::text(caption)),
				html::div(html::className("dropdown-menu"), html::Attribute("aria-labelledby", "navbarDropdown"), r...));
		}
		
		template<typename...R>
		webi::html::Tag navDropdownItem(const std::string& caption, R...r) { 
			return webi::html::Tag("a", { html::className("dropdown-item") }, html::text(caption), r...);
		}

		inline webi::html::Tag navDropdownDivider() {
			return html::div(html::className("dropdown-divider"));
		}

		class Button : public webi::html::Tag {
		public:
			inline const static auto Primary = html::Attribute("class", "btn-primary");
			inline const static auto Secondary = html::Attribute("class", "btn-secondary");

			inline const static auto Success = html::Attribute("class", "btn-success");
			inline const static auto Danger = html::Attribute("class", "btn-danger");
			inline const static auto Warning = html::Attribute("class", "btn-warning");
			inline const static auto Info = html::Attribute("class", "btn-info");

			inline const static auto Light = html::Attribute("class", "btn-light");
			inline const static auto Dark = html::Attribute("class", "btn-dark");

			inline const static auto Link = html::Attribute("class", "btn-link");

			inline const static auto Small = html::Attribute("class", "btn-sm");
			inline const static auto Large = html::Attribute("class", "btn-lg");
		};

		template<typename...R>
		webi::html::Tag button(const std::string& caption, const html::Attribute& _id, R...r) {
			return webi::html::Tag("button", 
				html::Attribute("type", "button"), html::className("btn"),
				html::text(caption), 
				_id,
				//Attribute("onclick", "webi.on_action_event('input', 'button', 'onclick', '" + _id.getValue() + "')"),
				r...);
		}

		template<typename...R>
		webi::html::Tag card(R...r) {
			return html::div(html::className("card"), html::div(html::className("card-body"), r...));
		}

		template<typename...R>
		webi::html::Tag cardTitle(const std::string& title, R...r) {
			return html::h5(html::className("card-title"), html::text(title),	r...);
		}

		template<typename...R>
		webi::html::Tag cardSubtitle(const std::string& title, R...r) {
			return html::h6(html::className("card-subtitle", "mb-2"), html::text(title), r...);
		}

		template<typename...R>
		webi::html::Tag cardText(const std::string& title, R...r) {
			return html::p(html::className("card-text"), html::text(title), r...);
		}

		template<typename... R>
		webi::html::Tag modal(const html::Attribute& id_, R...r) {
			return html::div(html::className("modal", "fade"), id_,
				html::Attribute("tabindex", "-1"),
				html::Attribute("role", "dialog"),
				html::Attribute("aria-labelledby", "exampleModalLongTitle"),
				html::Attribute("aria-hidden", "true"),
					html::div(html::className("modal-dialog"), 
						html::Attribute("role", "document"),
					html::div(html::className("modal-content"), r...))
			);
		}

		template<typename... R>
		webi::html::Tag modalHeader(R...r) {
			return html::div(html::className("modal-header"), r...);
		}

		template<typename... R>
		webi::html::Tag modalFooter(R...r) {
			return html::div(html::className("modal-footer"), r...);
		}


		template<typename... R>
		webi::html::Tag modalTitle(const std::string& title, R...r) {
			return html::h5(html::className("modal-title"), html::text(title), r...);
		}

		template<typename... R>
		webi::html::Tag modalBody(R...r) {
			return html::div(html::className("modal-body"), r...);
		}

		inline xml::AttributeSet modalToggle(const std::string& targetId) {
			return xml::AttributeSet({ html::Attribute("data-toggle", "modal"),
				html::Attribute("data-target", "#"+targetId) });
		}

		inline xml::AttributeSet modalOpen(const std::string& targetId) {
			return xml::AttributeSet({ html::Attribute("data-toggle", "modal"),
				html::Attribute("data-target", "#" + targetId) });
		}

		inline xml::AttributeSet modalClose(const std::string& targetId) {
			return xml::AttributeSet({ html::Attribute("data-toggle", "modal"),
				html::Attribute("data-target", "#" + targetId) });
		}

		inline html::Attribute modalDismiss() {
			return html::Attribute("data-dismiss", "modal");
		}

		template<typename...R>
		inline webi::html::Tag modalCloseButton(R...r) {
			return  webi::html::Tag("button", html::Attribute("type", "button"), html::className("close"), html::Attribute("data-dismiss", "modal"),
				html::Attribute("aria-label", "Close"),
				webi::html::Tag("span", html::Attribute("aria-hidden", "true"), html::text("&times;")),
				r...);
		}

		///---------------------- Slider ----------------------

		template<typename...R>
		webi::html::Tag slider(const std::string& idStr, int min, int max, int step, int value, R...r) {
			return webi::html::Tag("input", html::id(idStr), 
				html::Attribute("type", "text"),
				html::Attribute("data-slider-id", idStr + "Slider"),
				html::Attribute("data-slider-min", std::to_string(min)),
				html::Attribute("data-slider-max", std::to_string(max)),
				html::Attribute("data-slider-step", std::to_string(step)),
				html::Attribute("data-slider-value", std::to_string(value)),
				html::InitializerScript("$(\"#" + idStr + "\").slider().on(\"slide\", (e)=>{webi.on_action_event(\"slider\", \"text\", \"slide\", \"" + idStr + "\", e.value);});"),
				r...);
		}


		inline html::EventListener onslide(html::EventCallback cb) {
			return html::event("slide", cb);
		}

	};
};
