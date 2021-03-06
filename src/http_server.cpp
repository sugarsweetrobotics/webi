#include "webi/http_server.h"
#include "webi/webi.h"

using namespace webi;
using namespace webi::html;

void HttpServer::get(const std::string& path, Tag& tag) {
  webi_ptr_->parseEventListener(tag);
  response(path, "GET", "text/html", tag.toString());
}

