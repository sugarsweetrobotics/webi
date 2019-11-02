#pragma once

#include<vector>

namespace webi {

  namespace xml {
   class Attribute;
  }
  
  class GridLayoutStyler {
  private:
    std::vector<int32_t> column_widths_;
    std::vector<int32_t> row_heights_;

  public:
    GridLayoutStyler(const std::vector<int32_t>& column_widths, const std::vector<int32_t>& row_heights);
    virtual ~GridLayoutStyler();

  public:
    std::string containerStyleStr() const;
    std::string gridStyleStr(const int32_t x, const int32_t y, const int32_t width=1, const int32_t height=1) const;

  public:
    xml::Attribute containerStyle() const;
    xml::Attribute gridStyle(const int32_t x, const int32_t y, const int32_t width=1, const int32_t height=1) const;
  };


};
