#ifndef OAT_COLOR_HPP
#define OAT_COLOR_HPP


#include<cstdint>


namespace oat{


struct
Color
{
  uint8_t  r;
  uint8_t  g;
  uint8_t  b;

  constexpr Color(uint8_t  r_, uint8_t  g_, uint8_t  b_):
  r(r_),
  g(g_),
  b(b_){}

  constexpr Color(uint8_t  l=0):
  r(l),
  g(l),
  b(l){}

};


namespace palette{

using index_t = uint16_t;

const Color*  get_color(index_t  i);


}


namespace const_color{
constexpr Color  white(0xFF);
constexpr Color  black(0x00);
constexpr Color  red(0xFF,0x00,0x00);
constexpr Color  green(0x00,0xFF,0x00);
constexpr Color  blue(0x00,0x00,0xFF);
constexpr Color   yellow(0xFF,0xFF,0x00);
constexpr Color  mazenta(0xFF,0x00,0xFF);
constexpr Color     cyan(0x00,0xFF,0xFF);
constexpr Color        gray(0xAF);
constexpr Color   dark_gray(0x7F);
constexpr Color  light_gray(0xCF);
}


}




#endif




