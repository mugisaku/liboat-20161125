#ifndef OAT_FONT_HPP
#define OAT_FONT_HPP


#include<cstdint>


namespace oat{
namespace font{


constexpr int  size = 14;
constexpr int     top_padding = 4;
constexpr int  bottom_padding = 0;
constexpr int    left_padding = 2;
constexpr int   right_padding = 0;
constexpr int  line_margin  = 2;
constexpr int   width = left_padding+size+right_padding;
constexpr int  height = top_padding+size+bottom_padding+line_margin;

const uint32_t*  get_data(int  c);


}}


#endif




