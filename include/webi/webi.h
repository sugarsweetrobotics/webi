#pragma once

#include <string>
#include <memory>
#include "server.h"
#include "client.h"

#include "html.h"

namespace webi {

  class Webi {
  public:
    Webi();
    virtual ~Webi();

    Server_ptr createServer();
  };

};
