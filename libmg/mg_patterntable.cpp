#include"mg_patterntable.hpp"
#include"mg_core.hpp"




void
PatternTable::
change(int  x, int  y)
{
  data[y][x].reset(core::get_frame().x,core::get_frame().y);
}


const oat::Point&
PatternTable::
get(int  x, int  y) const
{
  return data[y][x];
}





