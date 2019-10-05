#pragma once

#include <cstdint>
#include <string>

#include "html.h"
#include "response.h"

namespace webi {
  class Server {
    
  public:
    Server() {}

    Server(Server&& s) {}

    virtual ~Server() {}
    
    virtual void baseDirectory(const std::string& path) = 0;
    
    virtual void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) = 0;

    void responseHTML(const std::string& path, const std::string& method, const std::string& content) {
      response(path, method, "text/html", content);
    }

    void getHTML(const std::string& path, const Tag& tag) {
      getHTML(path, tag.toString());

    }
    void getHTML(const std::string& path, const std::string& content) {
      response(path, "GET", "text/html", content);
    }

    virtual void runForever(const int32_t port=8080) = 0;
    
    virtual void runBackground(const int32_t port=8080) = 0;

    virtual void terminateBackground() = 0;
  };

  using Server_ptr = std::shared_ptr<Server>;
};
