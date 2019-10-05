#include "webi/server.h"

#include "cpp-httplib/httplib.h"


#include "webi/webi.h"

using namespace webi;

class ServerImpl : public Server{
private:
  httplib::Server server_;

public:
  ServerImpl();
  virtual ~ServerImpl();

  ServerImpl(ServerImpl&& server);

  void baseDirectory(const std::string& path) override;
  
  void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) override;

  void runForever(const int32_t port=8080) override;
    
  void runBackground(const int32_t port=8080) override;

  void terminateBackground() override;
};


ServerImpl::ServerImpl() {
}

ServerImpl::ServerImpl(ServerImpl&& server) {
}

ServerImpl::~ServerImpl() {

}

void ServerImpl::baseDirectory(const std::string& path) {
  server_.set_base_dir(path.c_str());

}

void ServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& response) {
  if (method == "GET") {
    server_.Get(path.c_str(), [response, contentType](const httplib::Request& req, httplib::Response& res) {
	res.set_content(response, contentType.c_str());
	res.status = 200;
      });
  }
}

void ServerImpl::runForever(const int32_t port /*=8080*/) {
  server_.listen("localhost", port);
}

void ServerImpl::runBackground(const int32_t port /*=8080*/) {
  std::string address = "127.0.0.1";
  const double timeout = 10.0;
  auto _port = port;
  if (port == 0) {
    _port = server_.bind_to_any_port(address.c_str(), 0);
  }
  auto thread = std::unique_ptr<std::thread>(new std::thread([&] { 
	if (port == 0) {
	  if (server_.listen_after_bind()) {
	  }
	} else {
	  if (server_.listen(address.c_str(), port)) {
	  }
	}
      }));
    
  auto t = std::chrono::system_clock::now();
  for(;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    if (server_.is_running()) break;
    
    auto d = std::chrono::system_clock::now() - t;
    int to = (int)(timeout*1000);
    
    if (to != 0 && d > std::chrono::milliseconds(to)) {
      //break;
    }
  }
}

void ServerImpl::terminateBackground() {
}

Server_ptr Webi::createServer() {
  return std::make_shared<ServerImpl>();
}



