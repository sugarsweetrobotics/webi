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
  H1(): Tag("H1") {}

    template<typename T, typename...R>
      H1(const T& t, R... r): Tag("H1", t, r...) {}
    virtual ~H1() {}
  };

  /**
   *
   */
  class P : public Tag {
  public:
  P(): Tag("P") {}

    template<typename T, typename...R>
      P(const T& t, R... r): Tag("P", t, r...) {}
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
    
  public:
    Button(const std::string& caption);
    virtual ~Button();

  public:
    static std::string generateOnClickedFunction(const Button* button);
  };

  /**
   *
   */
  class WebiScript : public Tag {
  private:


  public:
  WebiScript() : Tag("SCRIPT", Attribute("type", "text/javascript"), 
		     Attribute("src", "webi.js")) {}
    virtual ~WebiScript() {}

    static std::string generateWebiScript();
  };


};
