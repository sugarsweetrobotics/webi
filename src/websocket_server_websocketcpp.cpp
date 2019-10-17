
#include "webi/websocket_server.h"

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>


using namespace webi;



class WebSocketServerImpl : public WebSocketServer {


public:
  WebSocketServerImpl();

  virtual ~WebSocketServerImpl();

  virtual void runForever(const int32_t port=8081) override;

  virtual void runBackground(const int32_t port=8081) override;
 
  virtual bool waitBackground(const double timeout_sec=-1) override;
 
  virtual void terminateBackground() override;

};



WebSocketServerImpl::WebSocketServerImpl() {

}

WebSocketServerImpl::~WebSocketServerImpl() {

}

void WebSocketServerImpl::runForever(const int32_t port) {

}

void WebSocketServerImpl::runBackground(const int32_t port) {

}

bool WebSocketServerImpl::waitBackground(const double timeout_sec) {
  
  return false;
}

void WebSocketServerImpl::terminateBackground() {

}
