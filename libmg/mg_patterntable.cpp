#include"mg_patterntable.hpp"
#include"mg_core.hpp"




namespace pattern_table{


namespace{


oat::Point
data[size][size];


}


void
change(int  x, int  y)
{
  data[y][x].reset(core::get_frame().x,core::get_frame().y);
}


const oat::Point&
get(int  x, int  y)
{
  return data[y][x];
}




}
