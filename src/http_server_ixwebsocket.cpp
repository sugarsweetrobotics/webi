#include <iostream>

#include "webi/http_server.h"

//#include "cpp-httplib/httplib.h"
#include <ixwebsocket/IXHttpServer.h>

#include "webi/webi.h"
#include "webi_impl.h"

using namespace webi;

/*
static webi::Request convert(const httplib::Request &req)
{
  return webi::Request(req.method, req.body, req.matches);
}


static void apply(httplib::Response &response, webi::Response &&r)
{
  response.status = r.status;
  response.version = r.version;
  
  response.set_content(r.body, r.contentType.c_str());
    //  response.body = r.body;
}
*/

class ResponseFunction {
public:
  std::function<webi::Response(webi::Request&)> func;
  std::string path;
  std::string contentType;

public:
  ResponseFunction(const std::string& path, const std::string& contentType, std::function<webi::Response(webi::Request&)> func) : path(path), contentType(contentType), func(func) {}
};

class HttpServerImpl : public HttpServer{
private:
  //httplib::Server server_;
  ix::HttpServer *server_;
  std::unique_ptr<std::thread> thread_;
  std::vector<ResponseFunction> getters_;
  std::vector<ResponseFunction> posters_;
  std::vector<ResponseFunction> putters_;
  std::string baseDir_;
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


HttpServerImpl::HttpServerImpl() : baseDir_(".") {
}

HttpServerImpl::HttpServerImpl(HttpServerImpl&& server) {
}

HttpServerImpl::~HttpServerImpl() {

}

void HttpServerImpl::baseDirectory(const std::string& path) {
  //server_.set_base_dir(path.c_str());
  baseDir_ = path;
}

void HttpServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
  if (method == "GET") {
    getters_.emplace_back(ResponseFunction(path, contentType, callback));
  } else if (method == "PUT") {
    putters_.emplace_back(ResponseFunction(path, contentType, callback));
  } else if (method == "POST") {
    posters_.emplace_back(ResponseFunction(path, contentType, callback));
  }
}

void HttpServerImpl::runForever(const int32_t port /*=8080*/) {
  std::cout << "HttpServerImpl (IXWebSocket) runForever(" << port << ")" << std::endl;
  auto hostname = "0.0.0.0";
  server_ = new ix::HttpServer(port, hostname);
  auto [result, msg] = server_->listen();

  if (!result) {
    std::cerr << msg << std::endl;
    return;
  }

  server_->start();
  server_->wait();
}

void HttpServerImpl::runBackground(const int32_t port /*=8080*/) {
  std::string address = "localhost";
  const double timeout = 10.0;
  auto _port = port;
  thread_ = std::unique_ptr<std::thread>(new std::thread([port, this] {
							   this->runForever(port);
							 }));
}

bool HttpServerImpl::waitBackground(const double timeout_sec) {
  thread_->join();
  return true;
}

void HttpServerImpl::terminateBackground() {
  server_->stop();  
}

HttpServer_ptr WebiImpl::createHttpServerImpl() {
  std::cout << "WebiImpl::createHttpServerImpl(IXWebSocket)" << std::endl;
  auto svc = std::make_shared<HttpServerImpl>();

  std::cout << "exit2" << std::endl;
  return std::move(svc);
}



