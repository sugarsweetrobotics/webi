#pragma once

#include <string>
#include <vector>
#include <regex>

namespace webi {
  struct Response {
  public:
    std::string version;
    int32_t status;
    std::vector<Header> headers;
    std::string body;
  Response() : version("1.0"), status(0) {}
  Response(int32_t s) : version("1.0"), status(s), body("") {}
  Response(int32_t s, std::string &&body) : version("1.0"), status(s), body(body) {}
  Response(int32_t s, const std::string &body) : version("1.0"), status(s), body(body) {}
  Response(Response &&r) : version(r.version), status(r.status), body(r.body) {}
    Response& operator=(const Response&& r) {
      version = r.version;
      status = r.status;
      headers = r.headers;
      body = std::move(r.body);
      return *this;}
  };
  
  struct Request {
  public:
    std::string version;
    std::string method;
    std::string target;
    std::string path;
    std::vector<Header> headers;
    std::string body;
    std::smatch matches;
    void* _privateData;
  Request(const std::string &m, const std::string &b) : method(m), body(b), _privateData(nullptr) {}
  Request(std::string &&m, std::string &&b) : method(m), body(b), _privateData(nullptr) {}
  Request(const std::string &m, const std::string &b, const std::smatch &ms, void* privateData=nullptr) :
    method(m), body(b), matches(ms), _privateData(privateData) {}
  Request(std::string &&m, std::string &&b, std::smatch&& ms) : method(m), body(b), matches(ms), _privateData(nullptr) {}
  };
};
