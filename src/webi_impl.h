#pragma once

#include "webi/html.h"
#include "webi/webi_object.h"


struct AnyEventListener {
    std::string target;
    std::string type;
    webi::html::EventCallback callback;

    AnyEventListener(const std::string& tgt, const std::string& typ, const webi::html::EventCallback& cb) : target(tgt), type(typ), callback(cb) {}
};



class WebiImpl : public webi::IWebi {

public:

  WebiImpl() {};
  virtual ~WebiImpl() {};

    std::vector<AnyEventListener> eventListeners_;

    void addEventListener(const AnyEventListener& el) {
        eventListeners_.push_back(el);
    }
private:

    webi::HttpServer_ptr createHttpServer(webi::Server* ptr);
    webi::WebSocketServer_ptr createWebSocketServer(webi::Server* ptr);

private:
    webi::WebSocketServer_ptr createWebSocketServerImpl();
    webi::HttpServer_ptr createHttpServerImpl();

public:
    virtual webi::Server_ptr createServer() override;
    virtual void parseEventListener(webi::html::Tag& tag) override;

};

