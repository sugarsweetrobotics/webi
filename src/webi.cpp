#include "rapidjson/document.h"

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

  return std::make_shared<Server>(createHttpServer(), createWebSocketServer());
}



HttpServer_ptr Webi::createHttpServer() {
  auto s = createHttpServerImpl();
  s->setWebi(this);

  return s;
}

std::optional<WebiMessage> convert(const WebSocketMessage& msg) {
  rapidjson::Document document;
  //  std::cout << "msg.body = " << msg.body << std::endl;
  document.Parse(msg.body.c_str());
  
  if (!document["target"].IsString()) {
    return std::nullopt;
  }
  auto target = document["target"].GetString();
  if (!document["type"].IsString()) {
    return std::nullopt;
  }
  auto type   = document["type"].GetString();
  if (!document["id"].IsString()) {
    return std::nullopt;
  }
  auto id     = document["id"].GetString();
  if (!document["eventType"].IsString()) {
    return std::nullopt;
  }
  auto eventType = document["eventType"].GetString();
  
  return WebiMessage(target, type, id, eventType);
}

WebSocketServer_ptr Webi::createWebSocketServer() {
  auto s = createWebSocketServerImpl();
  s->setWebi(this);
  s->setOnOpenCallback([](const WebSocketConnectionInfo& info) {
      return true;
    });

  s->setOnMessageCallback([this](const WebSocketMessage& msg) {
      //std::cout << "on_message" << std::endl;
      auto m_ = convert(msg);
      if (m_) {
      for(auto e : this->eventListeners_) {
	auto m = m_.value();
	//std::cout << "WebiMessage come!" << std::endl;
	//std::cout << "  target: " << m.target << std::endl;
	//std::cout << "  type  : " << m.type << std::endl;
	if (m.id == e.target && m.eventType == e.type) {
	  e.callback(ActionEvent(e.target, "", e.type));
	}
      }
      return true;
      }
      return false;
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


