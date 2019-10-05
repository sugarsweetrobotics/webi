#include "webi/webi.h"

using namespace webi;

class ClientImpl : public Client{

    
public:
  ClientImpl();
  virtual ~ClientImpl();

  void get(const std::string& path, std::function<Response(Response&)> f);
};


ClientImpl::ClientImpl() {
}


ClientImpl::~ClientImpl() {
}


void ClientImpl::get(const std::string& path, std::function<Response(Response&)> f) {
}


Webi::Webi() {
}


Webi::~Webi() {
}

