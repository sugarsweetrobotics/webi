
#pragma once

#include <string>
#include <map>
#include <memory>
#include "server.h"
#include "client.h"
#include "websocket_server.h"
#include "html.h"

namespace webi {

  struct WebiMessage {
    std::string target;
    std::string type;
    std::string id;
    std::string eventType;

    WebiMessage(const std::string& target, 
		const std::string& type,
		const std::string& id,
		const std::string& eventType)
    : target(target), type(type), id(id), eventType(eventType) {}
  };

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

  public:
    Server_ptr createServer();

  private:
    
    HttpServer_ptr createHttpServer();
    WebSocketServer_ptr createWebSocketServer();

  private:
    WebSocketServer_ptr createWebSocketServerImpl();
    HttpServer_ptr createHttpServerImpl();

  public:
    void parse(const Tag& tag);

  private:
    void parseImpl(const Tag& tag);
    
  };

};
