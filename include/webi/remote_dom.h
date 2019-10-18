#pragma once


#include <optional>
#include <vector>
#include "webi/webi.h"

namespace webi {

  class RemoteElement;
  
  class Document;

  class Server;

  using RemoteElementList = std::vector<RemoteElement>;
  

  class RemoteElement {
  private:
    Document* doc_;

  public:
    Document& document() { return *doc_; }
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
    RemoteElement& setInnerHTML(const std::string& html);
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
