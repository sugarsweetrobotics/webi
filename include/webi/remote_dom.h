#pragma once


#include <optional>
#include <vector>
#include "webi/webi.h"

namespace webi {

	class RemoteElement;

	class Document;

	class Server;

	using RemoteElementList = std::vector<RemoteElement>;

	class ElementResponse {
	public:
		std::string target;
		std::string target_id;
		std::string value;
	};

	class RemoteElement {
	private:
		Document* doc_;

	public:
		Document& document() const { return *doc_; }
	private:
		std::optional<std::string> tag_name_;
		std::optional<std::string> id_;
		std::optional<std::string> classes_;

		RemoteElement* parent_;

	public:
		RemoteElement& setId(const std::string& id) {
			id_ = id;
			return *this;
		}
	public:
		void _setTagName(const std::string& tag_name) {
			tag_name_ = tag_name;
		}
	public:
		RemoteElementList children;

	public:
		RemoteElement(Document* doc);

		virtual ~RemoteElement() {}


	public:
		const RemoteElement& get(const std::string& key, std::function<void(const ElementResponse&)> callback) const;
		const RemoteElement& set(const std::string& key, const std::string& value) const;

		const RemoteElement& setInnerHTML(const std::string& html) const {
			return set("innerHTML", html);
		}

		const RemoteElement& getValue(std::function<void(const ElementResponse& response)> callback) const {
			return get("value", callback);
		}
	};

	class Document {
	private:

		Server* server_ptr_;

	public:
		Server& server() { return *server_ptr_; }
	public:
		Document(Server* server);
		~Document() {}

	public:
		RemoteElement body;

		RemoteElement getElementById(const std::string& id);
	};




};
