#include <iostream>

#include "webi/http_server.h"

#include "cpp-httplib/httplib.h"


#include "webi/webi.h"
#include "webi_impl.h"
#include "http_converter_cpphttplib.h"

using namespace webi;



class HttpServerImpl : public HttpServer{
private:
  httplib::Server server_;
  std::unique_ptr<std::thread> thread_;
public:
  HttpServerImpl();
  virtual ~HttpServerImpl();

  HttpServerImpl(HttpServerImpl&& server);

  void baseDirectory(const std::string& path) override;
  
  void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) override;

  void runForever(const int32_t port=8080) override;
    
  void runBackground(const int32_t port=8080) override;

  bool waitBackground(const double timeout_sec=-1) override;

  void terminateBackground() override;
};


HttpServerImpl::HttpServerImpl() {
}

HttpServerImpl::HttpServerImpl(HttpServerImpl&& server) {
}

HttpServerImpl::~HttpServerImpl() {

}

void HttpServerImpl::baseDirectory(const std::string& path) {
  server_.set_base_dir(path.c_str());

}

void HttpServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
  if (method == "GET") {
    server_.Get(path.c_str(), [callback, contentType](const httplib::Request& req, httplib::Response& res) {
	std::cout << "get response" << std::endl;
	apply(res, callback(convert(req)));
      });

  } else if (method == "PUT") {
    server_.Put(path.c_str(), [callback, contentType](const httplib::Request& req, httplib::Response& res) {
	std::cout << "put response" << std::endl;
	apply(res, callback(convert(req)));
      });
  }
  else if (method == "POST") {
    server_.Post(path.c_str(), [callback, contentType](const httplib::Request& req, httplib::Response& res) {
	std::cout << "post response" << std::endl;
	apply(res, callback(convert(req)));
      });
  }

}

void HttpServerImpl::runForever(const int32_t port /*=8080*/) {
  server_.listen("localhost", port);
}

void HttpServerImpl::runBackground(const int32_t port /*=8080*/) {
  std::string address = "localhost";
  const double timeout = 10.0;
  auto _port = port;
  if (port == 0) {
    _port = server_.bind_to_any_port(address.c_str(), 0);
  }

  /// Starting Thread 
  /*
  thread_ = std::unique_ptr<std::thread>(new std::thread([&] { 
	if (port == 0) {
	  if (server_.listen_after_bind()) {
	  }
	} else {
	  if (server_.listen(address.c_str(), port)) {
	  }
	}
      }));
  */

  thread_ = std::unique_ptr<std::thread>(new std::thread([port, this] {
	this->runForever(port);
      }));
}

bool HttpServerImpl::waitBackground(const double timeout_sec) {
  auto t = std::chrono::system_clock::now();
  for(;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    if (!server_.is_running()) {
      return true; // Server is ended
    }
    if (timeout_sec < 0) continue;

    auto d = std::chrono::system_clock::now() - t; // time_point
    int to = (int)(timeout_sec*1000);
    if (to > 0 && d > std::chrono::milliseconds(to)) {
      return false; // Timeout.
    }
  }
}

void HttpServerImpl::terminateBackground() {
  
}

HttpServer_ptr WebiImpl::createHttpServerImpl() {
  return std::make_shared<HttpServerImpl>();
}




webi::HttpServer_ptr webi::server() {
  return webi::HttpServer_ptr(new HttpServerImpl());
}
