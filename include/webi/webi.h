
#pragma once

#include <string>
#include <map>
#include <memory>
#include "server.h"
#include "client.h"
#include "websocket_server.h"
#include "html.h"

namespace webi {


  struct AnyEventListener {
    std::string target;
    std::string type;
    EventCallback callback;
  };
  
  class Webi {
  private:
    std::vector<AnyEventListener> eventListeners_;
  public:
    Webi();
    virtual ~Webi();

    Server_ptr createServer();
    WebSocketServer_ptr createWebSocketServer();


  private:
    WebSocketServer_ptr createWebSocketServerImpl();
    Server_ptr createServerImpl();

  public:
    void parse(const Tag& tag);

  private:
    void parseImpl(const Tag& tag);


    
  };

};
