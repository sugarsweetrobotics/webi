#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "webi/webi_common.h"

#include "html.h"
#include "response.h"
#include "http_server.h"
#include "websocket_server.h"

namespace webi {


  class WEBI_API Server {
  private:
    Webi_ptr webi_ptr_;

    void setWebi(Webi_ptr ptr) {
      webi_ptr_ = ptr;
    }

    Webi_ptr getWebi() { return webi_ptr_; }

    friend class Webi;

    HttpServer_ptr http_server_;
    WebSocketServer_ptr websock_server_;
  public:
  Server(HttpServer_ptr http_server, WebSocketServer_ptr websock_server) : http_server_(http_server), websock_server_(websock_server) {}

    virtual ~Server() {}
    
    virtual void baseDirectory(const std::string& path) {
      http_server_->baseDirectory(path);
    }
    
    virtual void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) {
      http_server_->response(path, method, contentType, content);
    }

    virtual void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
      http_server_->response(path, method, contentType, callback);
    }
    
    void get(const std::string& path, const Tag& tag) {
      http_server_->get(path, tag);
    }

    /**
     * Run Server on Current Thread. This function blocks until signal is raised..
     */
    virtual void runForever(const int32_t port=8080, const int32_t websock_port=8081) {
      websock_server_->runBackground();
      http_server_->runForever(port);
    }
    
    /**
     * Run Server on Background Thread.
     * @see waitBackground
     * @see terminateBackground
     */
    virtual void runBackground(const int32_t port=8080, const int32_t websock_port=8081) {
      http_server_->runBackground(port);
      websock_server_->runBackground(websock_port);
    }

    /**
     *
     * @param timeout_sec Timeout Interval. Forever if negative.
     * @return Server is ended if true. Timeout if false.
     */
    virtual bool waitBackground(const double timeout_sec=-1) {
      return http_server_->waitBackground(timeout_sec);
    }

    virtual void terminateBackground() {
      return http_server_->terminateBackground();
    }
  };

  using Server_ptr = std::shared_ptr<Server>;
};
