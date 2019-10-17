#include "webi/server.h"
#include "webi/webi.h"

using namespace webi;

void Server::get(const std::string& path, const Tag& tag) {
  webi_ptr_->parse(tag);
  response(path, "GET", "text/html", tag.toString());
}

