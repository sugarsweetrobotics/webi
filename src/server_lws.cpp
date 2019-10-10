#include <iostream>

#include "webi/server.h"


#include "webi/webi.h"

using namespace webi;

/*
webi::Request convert(const httplib::Request &req)
{
  return webi::Request(req.method, req.body, req.matches);
}


void apply(httplib::Response &response, webi::Response &&r)
{
  response.status = r.status;
  response.version = r.version;
  response.body = r.body;
}
*/

class ServerImpl : public Server{
private:

public:
  ServerImpl();
  virtual ~ServerImpl();

  ServerImpl(ServerImpl&& server);

  void baseDirectory(const std::string& path) override;
  
  void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) override;

  void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) override;

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

}

void ServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& response) {
  if (method == "GET") {
  }
}

void ServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
  if (method == "PUT") {
  }
  else if (method == "POST") {
  }

}

void ServerImpl::runForever(const int32_t port /*=8080*/) {

}

void ServerImpl::runBackground(const int32_t port /*=8080*/) {
}

void ServerImpl::terminateBackground() {
}

Server_ptr Webi::createServer() {
  return std::make_shared<ServerImpl>();
}



