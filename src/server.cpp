#include <sstream>

#include "webi/server.h"
#include "webi/webi.h"

using namespace webi;

Document Server::createDocument() {
  return Document(this);
}

struct ElementCommand {
  const std::string id;
  const std::string dir;
  const std::string cmd;
  const std::string arg;
};

static std::string convert(ElementCommand&& cmd) {
  std::stringstream ss;
  ss << "{\"type\":\"" << "element"
     << "\",\"id\":\"" << cmd.id 
     << "\",\"dir\":\"" << cmd.dir 
     << "\",\"cmd\":\"" << cmd.cmd 
     << "\",\"arg\":\"" << cmd.arg
     << "\"}";
  return ss.str();
}

void Server::elementCommandById(const std::string& id, 
			      const std::string& direction,
			      const std::string& command,
			      const std::string& arg) {
  websock_server_->send(convert({id, direction, command, arg}));
}


