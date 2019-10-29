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
		Attribute(Attribute&& a) : Attribute(std::move(a.key_), a.getValue()) {}

		Attribute& operator=(const Attribute& a) {
			this->key_ = a.getKey();
			this->value_ = a.getValue();
			return *this;
		}

		Attribute& operator=(Attribute&& a) {
			this->key_ = std::move(a.key_);
			this->value_ = a.getValue();
			return *this;
		}

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

	class Tag;

	using TagSet = std::vector<Tag>;

	class Tag {
	protected:
		std::map<std::string, EventCallback> eventListeners_;
	protected:
		std::string name_;
		std::string value_;
		AttributeSet attrs_;

	public:
		TagSet children;

	public:
		Tag(const Tag& tag) : name_(tag.name_), value_(tag.value_) {
			for (auto a : tag.attrs_)
				attrs_.push_back(a);
			for (auto t : tag.children)
				children.push_back(t);
			for (auto p : tag.eventListeners_) {
				eventListeners_[p.first] = p.second;
			}
		}

		Tag(Tag&& tag) : name_(std::move(tag.name_)), value_(std::move(tag.value_)),
			attrs_(std::move(tag.attrs_)),
			children(std::move(tag.children)), eventListeners_(std::move(tag.eventListeners_)) {
		}

		Tag& operator=(const Tag& tag) {
			this->name_ = tag.name_;
			this->value_ = tag.value_;

			for (auto a : tag.attrs_)
				attrs_.push_back(a);
			for (auto t : tag.children)
				children.push_back(t);
			for (auto p : tag.eventListeners_) {
				eventListeners_[p.first] = p.second;
			}
			return *this;
		}

		Tag& operator=(Tag&& tag) {
			this->name_ = std::move(tag.name_);
			this->value_ = std::move(tag.value_);
			this->attrs_ = std::move(tag.attrs_);
			this->children = std::move(tag.children);
			this->eventListeners_ = std::move(tag.eventListeners_);
			return *this;
		}

	public:

		Tag& setValue(const std::string& value) { value_ = value; return *this; }

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
		Tag();


		Tag(const std::string& name);

		Tag(const std::string& name, const TagSet& tag);

		Tag(const std::string& name, const AttributeSet& attrs);

		Tag(const std::string& name, const AttributeSet& attrs, const TagSet& tags);

		void init() {}

		auto init(Tag&& t) {
			children.emplace_back(t);
		}

		auto init(const Tag& t) {
			children.push_back(t);
		}

		template<typename T, typename...R>
		auto init(Tag&& t, T t2, R... r) {
			children.emplace_back(t);
			init(std::forward<T>(t2), r...);
		}

		template<typename T, typename...R>
		auto init(const Tag& t, T t2, R... r) {
			children.push_back(t);
			init(std::forward<T>(t2), r...);
		}

		template<typename A, typename...R>
		auto init(const A& t, R... r) -> typename std::enable_if<std::is_base_of<Attribute, A>::value>::type {
			attrs_.push_back(t);
			init(r...);
		}


		template<typename A, typename...R>
		auto init(A&& t, R... r) -> typename std::enable_if<std::is_base_of<Attribute, A>::value>::type {
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
		Tag(const std::string& name, T t, R... r) : name_(name) {
			init(std::forward<T>(t), r...);
		}

		template<typename...R>
		Tag(const std::string& name, const AttributeSet& attrs, R... r) : name_(name), attrs_(attrs) {
			init(r...);
		}

		template<typename...R>
		Tag::Tag(const std::string& name, Attribute&& att, R... r) : name_(name) {
			init(std::forward(att), r...);
		}

		virtual ~Tag();

		virtual std::string toString() const;

	private:
		void addAttribute(const Attribute& att) {
			attrs_.push_back(att);
		}
	};

	template<typename...R>
	Tag group(R... r) {
		return Tag("GROUP", r...);
	}

	inline Tag text(const std::string& value) {
		Tag t;
		t.setValue(value);
		return t;
	}


};
