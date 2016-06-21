#ifndef OAT_ICONMODULE_HPP
#define OAT_ICONMODULE_HPP


#include"oat_color.hpp"
#include<cstdio>


namespace oat{


constexpr uint16_t
Oo(int  n)
{
  return n;
}


struct
IconModule
{
  using octal_t = uint16_t;

  static constexpr int  size = 16;


  octal_t  map[size][size];

  void  print(FILE*  f=stdout) const;
  
};


namespace const_icon{
extern const IconModule  offcheck;
extern const IconModule   oncheck;
extern const IconModule  offradio;
extern const IconModule   onradio;
extern const IconModule     up;
extern const IconModule   down;
extern const IconModule   left;
extern const IconModule  right;
extern const IconModule  cross;
extern const IconModule  circle;
extern const IconModule  plus;
extern const IconModule  minus;
}


}




#endif




