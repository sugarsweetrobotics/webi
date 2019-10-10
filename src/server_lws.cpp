#include <iostream>

#include "webi/server.h"


#include "webi/webi.h"

#include <libwebsockets.h>
using namespace webi;


struct pss {
  char path[128];

  int times;
  int budget;

  int content_lines;
};

static const struct lws_http_mount _default_dynamic_mount = {
  /* .mount_next */NULL,/* linked-list "next" */
  /* .mountpoint */"/dyn",/* mountpoint URL */
  /* .origin */NULL, /* serve from dir */
  /* .def */NULL,/* default filename */
  /* .protocol */"http",
  /* .cgienv */NULL,
  /* .extra_mimetypes */NULL,
  /* .interpret */NULL,
  /* .cgi_timeout */0,
  /* .cache_max_age */0,
  /* .auth_mask */0,
  /* .cache_reusable */0,
  /* .cache_revalidate */0,
  /* .cache_intermediaries */0,
  /* .origin_protocol */LWSMPRO_CALLBACK,/* files in a dir */
  /* .mountpoint_len */4,/* char count */
  /* .basic_auth_login_file */NULL,
};

static const struct lws_http_mount _default_mount = {
  /* .mount_next */&_default_dynamic_mount,/* linked-list "next" */
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




static int _callback_dynamic_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);


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

class MountInfo;

class ServerImpl  : public Server {

private:
  std::string origin_;

  struct lws_http_mount mount_;

  struct lws_context_creation_info info_;

  struct lws_context *context_;

  std::vector<MountInfo> mountInfos_;

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


static int st = 6;

class MountInfo {
private:
  std::string method_;
  std::string origin_;
public:
  lws_http_mount mount;
  int id;
private:
  std::function<int(const Request& req, Response& res)> cb_;
public:
  lws_protocols protocol;


public:
  int callback(const Request& req, Response& res) {
    std::cout << "hooo" << std::endl;
    //    return cb_(req, res);
    return 0;
  }

  
public:
  MountInfo(const std::string& origin, 
	    const std::string& method, 
	    const uint32_t id, 
	    std::function<int(const Request& req, Response& res)> callback) : 
    origin_(origin),
    method_(method),
    mount(_default_dynamic_mount),
    cb_(callback) 
  {
    
    this->id = -5;
    protocol.name = "http";
    protocol.callback = _callback_dynamic_http;
    protocol.per_session_data_size = sizeof(MountInfo);
    protocol.rx_buffer_size = 0;
    protocol.id = id;
    protocol.user = (void*)this;
    protocol.tx_packet_size = 0;
    mount.origin = origin_.c_str();
  }
  
  ~MountInfo() {}


  MountInfo(const MountInfo&& mi) : method_(mi.method_),
				    origin_(mi.origin_),
				    mount(mi.mount),
				    cb_(mi.cb_),
				    protocol(mi.protocol) {
    this->id = -6;
    protocol.user = (void*)this;
  }

};


//static MountInfo mi("/", "hoge", 0, [](const Request& req, Response& res) {
//    std::cout << "Callback" << std::endl;
//  });

static int _callback_dynamic_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{

    uint8_t buf[LWS_PRE + 2048], *start = &buf[LWS_PRE], *p = start,
      *end = &buf[sizeof(buf) - LWS_PRE - 1];


    //  MountInfo& info = *(MountInfo*)user;
  Request req("GET", "body");
  Response res;
  //info.callback(req, res);

  std::cout << "callback(" << reason << std::endl;
  switch (reason) {
  case LWS_CALLBACK_HTTP: {
    std::cout << "hogeeee" << std::endl;

  char* puri;
  int   plen;
  int method = lws_http_get_uri_and_method(wsi, &puri, &plen);

  std::cout << "Method = " << method << std::endl;
  std::cout << "URI = " << puri << std::endl;


  MountInfo& info = *(MountInfo*)(lws_wsi_user(wsi));


    Request req("GET", "body");
    Response res;
    //const char* buf = "Hello LWS";
    //uint8_t* p = (uint8_t*)buf;
    //uint8_t* end = p + 8;
    //uint8_t* start = p;
    
    char* b = (char*)"Hello LWS";
    char* universal_response = b;
    

    info.callback(req, res);
    ///std::cout << "info_data:" << *(int*)user << std::endl;
    //    *(int*)user = 6;
    std::cout << "info:" << info.id << std::endl;
    if (lws_add_http_common_headers(wsi, HTTP_STATUS_OK,
				    "text/html",
				    LWS_ILLEGAL_HTTP_CONTENT_LEN, /* no content len */
				    &p, end)) {
	std::cout << "failed." << std::endl;
      return 1;
    }
    if (lws_finalize_write_http_header(wsi, start, &p, end)) {
      std::cout << "failed 2." << std::endl;
      return 1;
    }


    //lws_write(wsi, (uint8_t*)universal_response,
    //8, LWS_WRITE_HTTP);
    //std::cout << "written" << std::endl;
    //lws_close_and_free_session(context_, wsi, LWS_CLOSE_STATUS_NORMAL);
    //info.callback(req, res);
    /*
    if (lws_add_http_common_headers(wsi, HTTP_STATUS_OK,
				    "text/html",
				    8,
				    //LWS_ILLEGAL_HTTP_CONTENT_LEN, 
				    &p, end)) {
*/
    //    lws_http_transaction_completed(wsi);
    std::cout << "headerclose" << std::endl;

    lws_callback_on_writable(wsi);

    return 0;
  }
    break;

  case LWS_CALLBACK_HTTP_WRITEABLE: {
    std::cout << "Writeable" << std::endl;
    static const char* buf = "Hello LWS";

    MountInfo& info = *(MountInfo*)user;
    std::cout << "info_value:" << *(int*)user << std::endl;
    //    static uint8_t* p = (uint8_t*)buf;
    for(int i = 0;i < 9;i++) {
      p[i] = buf[i];
    }
    uint8_t* start = p;

    static int init;
    if (!init) {
    lws_write(wsi, (uint8_t *)start, 9, LWS_WRITE_HTTP);

    } else {
      lws_write(wsi, (uint8_t *)start, 9, LWS_WRITE_HTTP_FINAL);
    }

    
    if (!init) {
      lws_callback_on_writable(wsi);
      init++;
    } else {
    if (lws_http_transaction_completed(wsi)) {
      return -1;
    }
    }

      }

    return 0;
    break;

  default:
    return lws_callback_http_dummy(wsi, reason, user, in, len);
  };

  return lws_callback_http_dummy(wsi, reason, user, in, len);

}



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
    mountInfos_.emplace_back(MountInfo(path, method, 0, [response](const Request& req, Response& res) {
	  res.status = 200;
	  res.body = response;
	  return 0;
	}));
  }
}

void ServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
  if (method == "PUT") {
  }
  else if (method == "POST") {
  }
  else if (method == "GET") {
    mountInfos_.emplace_back(MountInfo(path, method, 0, [callback](const Request& req, Response& res) {
	  res = callback(req);
	  return 0;
	}));
  }

}

static int _interrupted = 0;
static void _sigint_handler(int sig)
{
  _interrupted = 1;
}

void ServerImpl::runForever(const int32_t port /*=8080*/) {


  struct lws_protocols** pprotocols = new lws_protocols*[mountInfos_.size()+1]; 
  for(int i = 0;i < mountInfos_.size();i++) {
    pprotocols[i] = &(mountInfos_[i].protocol);
  }
  pprotocols[mountInfos_.size()] = NULL;
  
  signal(SIGINT, _sigint_handler);

  memset(&info_, 0, sizeof info_); /* otherwise uninitialized garbage */
  info_.port = port;
    info_.mounts = &mount_;
    info_.pprotocols = (const lws_protocols**)pprotocols;

  info_.options = 0;//  LWS_SERVER_OPTION_EXPLICIT_VHOSTS | 
  //LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;
  
  context_ = lws_create_context(&info_);
  if (!context_) {
    lwsl_err("lws init failed\n");
    return;
  }

  //info_.port = port;
  //  info_.mounts = &mount_;
  //  info_.pprotocols = (const lws_protocols**)pprotocols;
  //info_.vhost_name = "http";
  //  if (!lws_create_vhost(context_, &info_)) {
  //    lwsl_err("Failed to create tls vhost\n");
  //    lws_context_destroy(context_);
  //    return ;
  //  }

  /*
  info_.port = port+1;
  info_.mounts = &mount_;
  info_.error_document_404 = "/404.html";
  info_.vhost_name = "localhost";
  if (!lws_create_vhost(context_, &info_)) {
    lwsl_err("Failed to create tls vhost\n");
    lws_context_destroy(context_);
    return ;
  }
  */

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



