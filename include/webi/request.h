#pragma once

#include <string>
#include <vector>
#include <regex>

#include "webi/header.h"

namespace webi {
  
  struct Request {
  public:
    std::string version;
    std::string method;
    std::string target;
    std::string path;
    std::vector<Header> headers;
    std::string body;
    std::string contentType;
    std::smatch matches;
    void* _privateData;
  Request(const std::string &m, const std::string &b, const std::string &ct) : method(m), body(b), _privateData(nullptr), contentType(ct) {}
  Request(std::string &&m, std::string &&b, std::string& ct) : method(m), body(b), _privateData(nullptr), contentType(ct) {}
  Request(const std::string &m, const std::string &b, const std::string& contentType, const std::smatch &ms, void* privateData=nullptr) :
    method(m), body(b), matches(ms), _privateData(privateData), contentType(contentType) {}

  Request(std::string &&m, std::string &&b, std::string&& ct, std::smatch&& ms) : method(m), body(b), matches(ms), _privateData(nullptr), contentType(ct) {}

  Request(std::string &&m, std::string &&b, std::vector<Header>&& headers, std::smatch&& ms) : method(m), body(b), matches(ms), _privateData(nullptr), headers(headers) {
    for(auto& h : headers) {
      if (h.first == "Content-Type") contentType = h.second;
    }
  }
  Request(const std::string &m, const std::string &b, const std::vector<Header>& headers, const std::smatch& ms) : method(m), body(b), matches(ms), _privateData(nullptr), headers(headers) {
    for(auto& h : headers) {
      if (h.first == "Content-Type") contentType = h.second;
    }
  }

  Request(std::string &&m, std::string &&b, std::vector<Header>&& headers) : method(m), body(b), _privateData(nullptr), headers(headers) {
    for(auto& h : headers) {
      if (h.first == "Content-Type") contentType = h.second;
    }
  }
  Request(const std::string &&m, const std::string &b, const std::vector<Header>& headers) : method(m), body(b), _privateData(nullptr), headers(headers) {
    for(auto& h : headers) {
      if (h.first == "Content-Type") contentType = h.second;
    }
  }
  };
};
