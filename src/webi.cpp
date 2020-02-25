#include <sstream>
#include <iostream>

#include "rapidjson/document.h"
#include "webi/webi.h"
#include "webi_impl.h"

#include "webi/js.h"

using namespace webi;
using namespace webi::html;

Webi::Webi() : impl_(new WebiImpl()) {
  //std::cout << "webi::webi()" << std::endl;
}

Webi::~Webi() { delete impl_; }

