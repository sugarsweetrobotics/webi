#include "rapidjson/document.h"

#include "webi/webi.h"

using namespace webi;

class ClientImpl : public Client {


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





HttpServer_ptr Webi::createHttpServer(Server_ptr ptr) {
	auto s = createHttpServerImpl();
	s->setWebi(this);

	return s;
}

std::optional<WebiMessage> convert(const WebSocketMessage& msg) {
	rapidjson::Document document;
	//  std::cout << "msg.body = " << msg.body << std::endl;
	document.Parse(msg.body.c_str());

	std::string target = "";
	if (document.HasMember("target") && document["target"].IsString()) {
		target = document["target"].GetString();
	}

	std::string type = "";
	if (document.HasMember("type") && document["type"].IsString()) {
		type = document["type"].GetString();
	}

	std::string id = "";
	if (document.HasMember("id") && document["id"].IsString()) {
		id = document["id"].GetString();
	}

	auto eventType = "";
	if (document.HasMember("eventType") && document["eventType"].IsString()) {
		eventType = document["eventType"].GetString();
	}

	auto body = "";
	if (document.HasMember("body") && document["body"].IsString()) {
		body = document["body"].GetString();
	}

	auto value = "";
	if (document.HasMember("value") && document["value"].IsString()) {
		value = document["value"].GetString();
	}

	return WebiMessage(target, type, id, eventType, body, value);
}

WebSocketServer_ptr Webi::createWebSocketServer(Server_ptr ptr) {
	auto s = createWebSocketServerImpl();
	s->setWebi(this);
	s->setOnOpenCallback([](const WebSocketConnectionInfo& info) {
		return true;
	});

	s->setOnMessageCallback([this, ptr](const WebSocketMessage& msg) {
		//std::cout << "on_message" << std::endl;
		auto m_ = convert(msg);
		if (m_) {  

			if (ptr->parseBookedResponse(m_.value())) {
				return true;
			}

			for (auto e : this->eventListeners_) {
				auto m = m_.value();
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
	for (auto c : tag.children) {
		parse(c);
	}
}

void Webi::parseImpl(const Tag& tag) {
	if (tag.hasAttribute("onclick") && tag.hasAttribute("id")) {
		auto id = tag.attribute("id");
		auto cb = tag.eventListener("onclick");
		if (cb) {
			eventListeners_.push_back({ id, "onclick", cb.value() });
		}
	}
}


