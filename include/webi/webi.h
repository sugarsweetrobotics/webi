
#pragma once

#include <string>
#include <map>
#include <memory>
#include "server.h"
#include "client.h"
#include "websocket_server.h"
#include "html.h"
#include "css.h"
#include "remote_dom.h"

namespace webi {

  struct WebiMessage {
    std::string target;
    std::string type;
    std::string id;
    std::string eventType;
	std::string body;
	std::string value;

    WebiMessage(const std::string& target, 
		const std::string& type,
		const std::string& id,
		const std::string& eventType,
		const std::string& body,
		const std::string& value)
    : target(target), type(type), id(id), eventType(eventType), body(body), value(value) {}
  };

  struct AnyEventListener {
    std::string target;
    std::string type;
    EventCallback callback;

	AnyEventListener(const std::string& tgt, const std::string& typ, const EventCallback& cb) : target(tgt), type(typ), callback(cb) {}
  };

  class Document;
  
  class Webi {
  private:
    std::vector<AnyEventListener> eventListeners_;
  public:
	  void addEventListener(AnyEventListener& el) {
		  eventListeners_.push_back(el);
	  }

  public:
    Webi();
    virtual ~Webi();

  public:
    Server_ptr createServer();
  private:
    
    HttpServer_ptr createHttpServer(Server_ptr ptr);
    WebSocketServer_ptr createWebSocketServer(Server_ptr ptr);

  private:
    WebSocketServer_ptr createWebSocketServerImpl();
    HttpServer_ptr createHttpServerImpl();

  public:
    void parseEventListener(Tag& tag);

  public:
  };

};
