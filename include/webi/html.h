#pragma once

#include <string>
#include <vector>

#include "xml.h"


namespace webi {

  class Style : public Attribute {
  public:
  Style(const std::string& value) : Attribute("style", value) {}
    virtual ~Style() {}
  };

  class HTML : public Tag {
  public:
  HTML() : Tag("HEADER") {}

    template<typename T, typename...R> 
      HTML(const T& t, R... r) : Tag("HTML", t, r...) {}
    virtual ~HTML() {}
  };


  class Header : public Tag {
  public:
  Header() : Tag("HEADER") {}

    template<typename T, typename...R> 
      Header(const T& t, R... r) : Tag("HEADER", t, r...) {}
    virtual ~Header() {}
  };

  class Body : public Tag {
  public:
  Body() : Tag("HEADER") {}

    template<typename T, typename...R> 
      Body(const T& t, R... r) : Tag("BODY", t, r...) {}
    virtual ~Body() {}
  };



  class StyleSheet : public Tag {
  private:
  public:
  StyleSheet(const std::string& ref) : Tag("LINK", Attribute("rel", "stylesheet"),
					   Attribute("type", "text/css"),
					   Attribute("href", ref)) {}
    virtual ~StyleSheet() {}
  };

  class Button : public Tag {
  private:
    
  public:
    Button(const std::string& caption);
    virtual ~Button();

  public:
    static std::string generateOnClickedFunction(const Button* button);
  };


  class WebiScript : public Tag {
  private:


  public:
  WebiScript() : Tag("SCRIPT", Attribute("type", "text/javascript"), 
		     Attribute("src", "webi.js")) {}
    virtual ~WebiScript() {}

    static std::string generateWebiScript();
  };


};
