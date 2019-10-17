#include "webi/webi.h"

using namespace webi;

class ClientImpl : public Client{

    
public:
  ClientImpl();
  virtual ~ClientImpl();

  void get(const std::string& path, std::function<Response(Response&)> f);
};


ClientImpl::ClientImpl() {
}


ClientImpl::~ClientImpl() {
}


void ClientImpl::get(const std::string& path, std::function<Response(Response&)> f) {
}


Webi::Webi() {

}


Webi::~Webi() {
}


Server_ptr Webi::createServer() {
  auto s = createServerImpl();
  s->setWebi(this);

  return s;
}

WebSocketServer_ptr Webi::createWebSocketServer() {
  auto s = createWebSocketServerImpl();
  s->setWebi(this);
  s->setOnOpenCallback([](const WebSocketConnectionInfo& info) {
      return true;
    });

  s->setOnMessageCallback([](const WebSocketMessage& msg) {
      return true;
    });

  return s;
}

void Webi::parse(const Tag& tag) {
  parseImpl(tag);
  for(auto c : tag.children) {
    parse(c);
  }
}

void Webi::parseImpl(const Tag& tag) {
  if (tag.hasAttribute("onclick") && tag.hasAttribute("id")) {
    auto id = tag.attribute("id");
    auto cb = tag.eventListener("onclick");
    if (cb) {
      eventListeners_.push_back({id, "onclick", cb.value()});
    }
  }
}
