#pragma once

#include <iostream>

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "webi/webi_common.h"

#include "webi/html.h"
#include "webi/response.h"
#include "webi/request.h"

namespace webi {

  class WEBI_API HttpClient {
  public:
    
  public:
    HttpClient() {}

    HttpClient(HttpClient&& s) {}

    virtual ~HttpClient() {}

  public:
    
    virtual void setTimeout(uint64_t seconds) = 0;
    virtual Response request(const std::string& url, const std::string& method) = 0;
    virtual Response request(const std::string& url, const std::string& method, const Request& req) = 0;
  };
  
  using HttpClient_ptr = std::shared_ptr<HttpClient>;

  webi::HttpClient_ptr client(const std::string& addr, const int port);
};
