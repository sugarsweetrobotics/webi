#pragma once

#include <string>

#include "response.h"

namespace webi {
  class Client {
    
  public:
    Client() {};

    Client(Client& c) {}

    virtual ~Client() {}

    virtual void get(const std::string& path, std::function<Response(Response&&)> f) = 0;
  };
};
