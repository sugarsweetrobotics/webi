#include <sstream>
#include <iostream>

#include "rapidjson/document.h"
#include "webi/webi.h"
#include "webi_impl.h"

using namespace webi;
using namespace webi::html;

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


Webi::Webi() : impl_(new WebiImpl()) {
std::cout << "webi::webi()" << std::endl;

}

Webi::~Webi() { delete impl_; }

WebiImpl::WebiImpl() {
	std::cout << "webiimpl" << std::endl;
}

WebiImpl::~WebiImpl() {
}

HttpServer_ptr WebiImpl::createHttpServer(Server_ptr ptr) {
	auto s = createHttpServerImpl();
	s->setWebi(this);
	return s;
}

std::optional<WebiMessage> convert(const WebSocketMessage& msg) {
	rapidjson::Document document;
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

WebSocketServer_ptr WebiImpl::createWebSocketServer(Server_ptr ptr) {
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
					e.callback(ActionEvent(e.target, "", e.type, m.value));
				}
			}
			return true;
		}
		return false;
	});

	return s;
}

void parseEventListenerImpl(WebiImpl* this_, std::vector<webi::html::InitializerScript> &inits, Tag& tag) {
	auto id = tag.attribute("id");
	for (auto cb : tag.eventListeners()) {
		this_->addEventListener(AnyEventListener(id, cb.name(), cb.callback()));
		
		if (cb.name() == "click") {
			auto o = js::Document().getElementById(id).addEventListener(cb.name(), 
				js::lambda("e").define( js::Webi().on_action_event("input", "button", cb.name(), id) )
			);
			tag.addInitializerScript(InitializerScript(o.expression()));
		}
	}

	if (tag.hasInitializerScript()) {
		for(auto i : tag.initializers()) {
			inits.emplace_back(i);
		}
	}

	for (auto c : tag.children) {
		parseEventListenerImpl(this_, inits, c);
	}
}

void appendInitializerImpl(const std::vector<InitializerScript> &inits, Tag& tag) {
	std::stringstream ss;
	for (auto i : inits) {
		ss << i.toString();
	}
	if (tag.name() == "BODY") {
		tag.children.push_back(
			script(scriptType("text/javascript"),
				text("document.addEventListener(\"DOMContentLoaded\", function() {" +
					ss.str() +
					"});"
				)
			)
		);
	}
	else {
		for (int i = 0; i < tag.children.size(); i++) {
			appendInitializerImpl(inits, tag.children[i]);
		}
	}
}


void WebiImpl::parseEventListener(Tag& tag) {
	std::vector<InitializerScript> initializers;
	parseEventListenerImpl(this, initializers, tag);
	appendInitializerImpl(initializers, tag);
}
