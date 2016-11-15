#include"mg_patterntable.hpp"
#include"mg_core.hpp"




namespace pattern_table{


namespace{


int
data[size][size];


}


void
change(int  x, int  y)
{
  data[y][x] = core::get_y_offset();
}


int
get(int  x, int  y)
{
  return data[y][x];
}




}
