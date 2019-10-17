#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>
#include <map>

#include "webi/webi_common.h"

#include "html.h"
#include "response.h"

namespace webi {

  struct WebSocketConnectionInfo {
    std::string uri;
    std::map<std::string, std::string> headers;
  };

  struct WebSocketMessage {
    std::string body;
  };

  class WEBI_API WebSocketServer {
  private:
    Webi_ptr webi_ptr_;

  public:
    void setWebi(Webi_ptr ptr) { webi_ptr_ = ptr; }
  public:
    WebSocketServer() {}

    //WebSocketServer(WebSocketServer&& s) {}

    virtual ~WebSocketServer() {}

    virtual void setOnOpenCallback(std::function<bool(const WebSocketConnectionInfo&)> callback) = 0;

    virtual void setOnMessageCallback(std::function<bool(const WebSocketMessage&)> callback) = 0;

    virtual void runForever(const int32_t port=8081) = 0;
    
    virtual void runBackground(const int32_t port=8081) = 0;

    virtual bool waitBackground(const double timeout_sec=-1) = 0;

    virtual void terminateBackground() = 0;
  };

  using WebSocketServer_ptr = std::shared_ptr<WebSocketServer>;
};
