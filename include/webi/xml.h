#pragma once

#include <string>
#include <vector>

namespace webi {
  class Attribute {
  private:
    std::string key_;
    std::string value_;
  public:
    Attribute(const std::string& key, const std::string& value);
    virtual ~Attribute();
    std::string toString() const;
  };

  using AttributeSet = std::vector<Attribute>;

  class Tag {
  protected:
    std::string name_;
    std::string value_;
    AttributeSet attrs_;
  public:
    std::vector<Tag> children;

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
  };

  class Text : public Tag {
  public:
    Text(const std::string& value);
    virtual ~Text();
  };

};
