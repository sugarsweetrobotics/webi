#pragma once

#include <string>
#include <vector>
#include <map>

#include <optional>

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

  public:
    std::string getKey() const { return key_; }
    std::string getValue() const { return value_; }

  public:
    Attribute(const std::string& key, const std::string& value);
    virtual ~Attribute();
    std::string toString() const;
  };

  using AttributeSet = std::vector<Attribute>;


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
      auto i  = eventListeners_.find(key);
      if (i == eventListeners_.end()) {
	return std::nullopt;
      }

      return i->second;
    }

    std::string attribute(const std::string& key) const {
      for(auto a : attrs_) {
	if (a.getKey() == key) return a.getValue();
      }
      return "";
    }

    bool hasAttribute(const std::string& key) const {
      for(auto a : attrs_) {
	if (a.getKey() == key) return true;
      }

      return false;
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

  class Text : public Tag {
  public:
    Text(const std::string& value);
    virtual ~Text();
  };



};
