#pragma once

#include <string>
#include <vector>
#include <map>

#include <optional>
#include <functional>
#include "webi/webi_common.h"

namespace webi {

	struct ActionEvent {
		std::string target_id;
		std::string name;
		std::string type;

		ActionEvent(const std::string& target_id,
			const std::string& name,
			const std::string& type)
			: target_id(target_id), name(name), type(type) {}
	};

	using EventCallback = std::function<void(const ActionEvent&)>;

	class Attribute {

	private:
		std::string key_;
		std::string value_;

		std::optional<std::function<std::string()>> value_callback_;

	public:
		std::string getKey() const { return key_; }
		std::string getValue() const { 
			if (value_callback_) {
				return value_callback_.value()();
			}
			return value_; 
		}

		void setValue(const std::string& value) { value_ = value; }
	public:
		Attribute(const std::string& key, const std::string& value);
		Attribute(const std::string& key, std::function<std::string()> cb);
		virtual ~Attribute();
		std::string toString() const;

		Attribute(const Attribute& a) : Attribute(a.getKey(), a.getValue()) {}

	public:
		bool operator==(const Attribute& a) const {
			return (key_ == a.key_ && value_ == a.value_);
		}
	};

	using AttributeSet = std::vector<Attribute>;

	class EventListener {
	private:
		std::string name_;
		EventCallback callback_;
	public:
		std::string name() const { return name_; }
		EventCallback callback() const { return callback_; }
	public:
		EventListener(const std::string& name, EventCallback callback) : name_(name), callback_(callback) {}
	};

	class Server;

	class Tag {
	protected:
		std::map<std::string, EventCallback> eventListeners_;
	protected:
		std::string name_;
		std::string value_;
		AttributeSet attrs_;

	public:
		std::vector<Tag> children;

	public:
		std::string name() const { return name_; }

		std::optional<EventCallback> eventListener(const std::string& key) const {
			auto i = eventListeners_.find(key);
			if (i == eventListeners_.end()) {
				return std::nullopt;
			}

			return i->second;
		}

		std::string attribute(const std::string& key) const {
			for (auto a : attrs_) {
				if (a.getKey() == key) return a.getValue();
			}
			return "";
		}

		bool hasAttribute(const std::string& key) const {
			for (auto a : attrs_) {
				if (a.getKey() == key) return true;
			}

			return false;
		}

		std::string getAttribute(const std::string& key) const  {
			std::string buf;
			for (auto a : attrs_) {
				if (a.getKey() == key) {
					if (buf.length() > 0) buf += " ";
					buf += a.getValue();
				}
			}
			return buf;
		}

		std::string getID() const {
			return getAttribute("id");
		}
	public:
		Tag(const std::string& name);

		Tag(const std::string& name, AttributeSet attrs);

		void init() {}

		template<typename T, typename...R>
		auto init(const T& t, R... r) -> typename std::enable_if<std::is_base_of<Tag, T>::value>::type {
			children.push_back(t);
			init(r...);
		}

		template<typename A, typename...R>
		auto init(const A& t, R... r) -> typename std::enable_if<std::is_base_of<Attribute, A>::value>::type {
			attrs_.push_back(t);
			init(r...);
		}
	
		template<typename E, typename...R>
		auto init(const E& t, R... r) -> typename std::enable_if<std::is_base_of<EventListener, E>::value>::type {
			this->eventListeners_.emplace(t.name(), t.callback());
			attrs_.push_back(Attribute(t.name(), [this, t]() {
				return "webi.on_action_event('" + name() + "', '" + getAttribute("type") + "', '" + t.name() + "', '" + getID() + "')";
			}));
			init(r...);
		}
		
		template<typename T, typename...R>
		Tag(const std::string& name, const T& t, R... r) : name_(name) {
			init(t, r...);
		}

		template<typename T, typename...R>
		Tag(const std::string& name, AttributeSet attrs, const T& t, R... r) : name_(name), attrs_(attrs) {
			init(t, r...);
		}

		virtual ~Tag();

		void copyFrom(const Tag& tag) {
			children = tag.children;
			attrs_ = tag.attrs_;
		}

		virtual std::string toString() const;

	private:
		void addAttribute(const Attribute& att) {
			attrs_.push_back(att);
		}
	};

	class Group : public Tag {
	public:
		template<typename...R>
		Group(R... r) : Tag("GROUP", r...) {}
	public:
		virtual std::string toString() const override;
	};

	class Text : public Tag {
	public:
		Text(const std::string& value);
		virtual ~Text();
	};



};
