#pragma once

#include <string>
#include <vector>
#include <regex>

namespace webi {

	struct Header {

  };

  struct Response {
  public:
    std::string version;
    int32_t status;
    std::vector<Header> headers;
    std::string body;
    std::string contentType;
  Response() : version("1.0"), status(0) {}
  Response(int32_t s) : version("1.0"), status(s), body("") {}
  Response(int32_t s, std::string &&body, std::string&&  contentType) : version("1.0"), status(s), body(body), contentType(contentType) {}
  Response(int32_t s, const std::string &body, const std::string& contentType) : version("1.0"), status(s), body(body), contentType(contentType) {}
  Response(Response &&r) : version(r.version), status(r.status), body(r.body) {}
    Response& operator=(const Response&& r) {
      version = r.version;
      status = r.status;
      headers = r.headers;
      body = std::move(r.body);
      return *this;}
  };
  
};
