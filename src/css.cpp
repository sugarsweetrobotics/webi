#include <sstream>

#include "webi/css.h"
#include "webi/xml.h"


using namespace webi;


GridLayoutStyler::GridLayoutStyler(const std::vector<int32_t>& column_widths, const std::vector<int32_t>& row_heights) :
  column_widths_(column_widths), row_heights_(row_heights)
{
}

GridLayoutStyler::~GridLayoutStyler() {
}

std::string GridLayoutStyler::gridStyleStr(const int32_t x, const int32_t y, const int32_t width, const int32_t height) const {
  std::stringstream ss;
  ss << "grid-row:" << y+1 << "/span " << height << ";";
  ss << "grid-column:" << x+1 << "/span " << width << ";";
  ss << "margin: auto;";
  return ss.str();
}


std::string GridLayoutStyler::containerStyleStr() const {
  std::stringstream ss;
  ss << "display:grid;";
  ss << "grid-template-columns:";
  for(auto c: column_widths_) {
    if (c < 0) {
      ss << " " << "1fr";
    } else {
      ss << " " << c << "pt";
    }
  }
  ss << ";";

  ss << "grid-template-rows:";
  for(auto r: row_heights_) {
    if (r < 0) {
      ss << " " << "1fr";
    } else {
      ss << " " << r << "pt";
    }
  }
  ss << ";";

  return ss.str();
}


webi::Attribute GridLayoutStyler::containerStyle() const {
  return Attribute("style", containerStyleStr());
}

webi::Attribute GridLayoutStyler::gridStyle(const int32_t x, const int32_t y, const int32_t width, const int32_t height) const {
  return Attribute("style", gridStyleStr(x, y, width, height));
}
