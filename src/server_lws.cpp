#include <iostream>

#include "webi/server.h"


#include "webi/webi.h"

#include <libwebsockets.h>
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
  std::string origin_;
  struct lws_http_mount mount_;

  struct lws_context_creation_info info_;

  struct lws_context *context_;
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


static const struct lws_http_mount _default_mount = {
  /* .mount_next */NULL,/* linked-list "next" */
  /* .mountpoint */"/",/* mountpoint URL */
  /* .origin */"./www", /* serve from dir */
  /* .def */"index.html",/* default filename */
  /* .protocol */NULL,
  /* .cgienv */NULL,
  /* .extra_mimetypes */NULL,
  /* .interpret */NULL,
  /* .cgi_timeout */0,
  /* .cache_max_age */0,
  /* .auth_mask */0,
  /* .cache_reusable */0,
  /* .cache_revalidate */0,
  /* .cache_intermediaries */0,
  /* .origin_protocol */LWSMPRO_FILE,/* files in a dir */
  /* .mountpoint_len */1,/* char count */
  /* .basic_auth_login_file */NULL,
};

ServerImpl::ServerImpl() : mount_(_default_mount) {
}

ServerImpl::ServerImpl(ServerImpl&& server) {
}

ServerImpl::~ServerImpl() {

}

void ServerImpl::baseDirectory(const std::string& path) {
  origin_ = path;
  mount_.origin = origin_.c_str();
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

static int _interrupted = 0;
static void _sigint_handler(int sig)
{
  _interrupted = 1;
}

void ServerImpl::runForever(const int32_t port /*=8080*/) {

  signal(SIGINT, _sigint_handler);

  memset(&info_, 0, sizeof info_); /* otherwise uninitialized garbage */
  info_.port = port;
  info_.mounts = &mount_;
  info_.error_document_404 = "/404.html";
  info_.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;
  
  context_ = lws_create_context(&info_);
  if (!context_) {
    lwsl_err("lws init failed\n");
    return;
  }

  int n = 0;
  while (n >= 0 && _interrupted == 0) {
    n = lws_service(context_, 0);
  }

  lws_context_destroy(context_);
}

void ServerImpl::runBackground(const int32_t port /*=8080*/) {
}

void ServerImpl::terminateBackground() {
}

Server_ptr Webi::createServer() {
  return std::make_shared<ServerImpl>();
}



