#include <iostream>
#include "webi/webi.h"
#include "webi/websocket_server.h"

#include <ixwebsocket/IXWebSocketServer.h>

#include "webi_impl.h"

using namespace webi;

class WebSocketServerImpl : public WebSocketServer {
public:
  std::function<bool(const WebSocketConnectionInfo&)> cb_on_open_;
  std::function<bool(const WebSocketMessage&)> cb_on_message_;

public:
  ix::WebSocketServer *server_;

public:
  WebSocketServerImpl();

  virtual ~WebSocketServerImpl();

  virtual void setOnOpenCallback(std::function<bool(const WebSocketConnectionInfo&)> callback) override {
    cb_on_open_ = callback;
  }

  virtual void setOnMessageCallback(std::function<bool(const WebSocketMessage&)> callback) override {
    cb_on_message_ = callback;
  }

  virtual void send(const std::string& msg) override;

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
  //std::cout << "Starting Server..." << port << std::endl;
  ix::WebSocketServer server(port);


  server.setOnConnectionCallback([&server](std::shared_ptr<ix::WebSocket> webSocket, std::shared_ptr<ix::ConnectionState> connectionState) {
      webSocket->setOnMessageCallback([webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg) {
	  if (msg->type == ix::WebSocketMessageType::Open) {
	    std::cerr << "New connection" << std::endl;
	    
	    // A connection state object is available, and has a default id
	    // You can subclass ConnectionState and pass an alternate factory
	    // to override it. It is useful if you want to store custom
	    // attributes per connection (authenticated bool flag, attributes, etc...)
	    std::cerr << "id: " << connectionState->getId() << std::endl;
	    
	    // The uri the client did connect to.
	    std::cerr << "Uri: " << msg->openInfo.uri << std::endl;
	    
	    std::cerr << "Headers:" << std::endl;
	    for (auto it : msg->openInfo.headers) {
	      std::cerr << it.first << ": " << it.second << std::endl;
	    }
	  } else if (msg->type == ix::WebSocketMessageType::Message) {
	      // For an echo server, we just send back to the client whatever was received by the server
	      // All connected clients are available in an std::set. See the broadcast cpp example.
	      // Second parameter tells whether we are sending the message in binary or text mode.
	      // Here we send it in the same mode as it was received.
	      webSocket->send(msg->str, msg->binary);
	    }
	});
    });


  auto res = server.listen();
  if (!res.first)
    {
      // Error handling
      return ;
    }

  std::cout << "Starting Connection!" << std::endl;

  server.start();

}

void WebSocketServerImpl::runBackground(const int32_t port) {
  //std::cout << "Starting Server..." << port << std::endl;
  server_ = new ix::WebSocketServer(port);


  server_->setOnConnectionCallback([this](std::shared_ptr<ix::WebSocket> webSocket, std::shared_ptr<ix::ConnectionState> connectionState) {
      webSocket->setOnMessageCallback([webSocket, connectionState, this](const ix::WebSocketMessagePtr msg) {
	  if (msg->type == ix::WebSocketMessageType::Open) {
	    std::cerr << "New connection" << std::endl;
	    
	    // A connection state object is available, and has a default id
	    // You can subclass ConnectionState and pass an alternate factory
	    // to override it. It is useful if you want to store custom
	    // attributes per connection (authenticated bool flag, attributes, etc...)
	    std::cerr << "id: " << connectionState->getId() << std::endl;
	    
	    // The uri the client did connect to.
	    std::cerr << "Uri: " << msg->openInfo.uri << std::endl;
	    
	    std::cerr << "Headers:" << std::endl;
	    for (auto it : msg->openInfo.headers) {
	      std::cerr << it.first << ": " << it.second << std::endl;
	    }

	    this->cb_on_open_(WebSocketConnectionInfo());
	  } else if (msg->type == ix::WebSocketMessageType::Message) {
	      // For an echo server, we just send back to the client whatever was received by the server
	      // All connected clients are available in an std::set. See the broadcast cpp example.
	      // Second parameter tells whether we are sending the message in binary or text mode.
	      // Here we send it in the same mode as it was received.
	    //webSocket->send(msg->str, msg->binary);
	    std::cout << msg->str << std::endl;
	    this->cb_on_message_(WebSocketMessage(msg->str));
	  }
	});
    });


  auto res = server_->listen();
  if (!res.first)
    {
      // Error handling
      return ;
    }

  //std::cout << "Starting Connection!" << std::endl;

  server_->start();

}

bool WebSocketServerImpl::waitBackground(const double timeout_sec) {
  server_->wait();

  //std::cout << "Ending..." << std::endl;
  
  return true;
}

void WebSocketServerImpl::terminateBackground() {

}

void WebSocketServerImpl::send(const std::string& msg) {
  auto clients = server_->getClients();
  for(auto client : clients) {
    //    if (client->isConnected()) {
      client->send(msg);
      //}
  }
  
}

WebSocketServer_ptr WebiImpl::createWebSocketServerImpl() {
  return std::make_shared<WebSocketServerImpl>();
}
