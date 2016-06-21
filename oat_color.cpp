#include"oat_color.hpp"
#include<algorithm>




namespace oat{
namespace palette{




struct
Table
{
  Color  colors[0b1000000000];

  Table();

};


Table::
Table()
{
    for(int  b = 0;  b < 8;  ++b){
    for(int  g = 0;  g < 8;  ++g){
    for(int  r = 0;  r < 8;  ++r){
      int  i = ((r<<6)|(g<<3)|b);

      auto&  color = colors[i];

      color.r = r? ((r<<5)|0b11111):0;
      color.g = g? ((g<<5)|0b11111):0;
      color.b = b? ((b<<5)|0b11111):0;
    }}}
}




const Color*
get_color(index_t  i)
{
  static const Table   tbl;

  return((i>>9)? &tbl.colors[i&0b111111111]:nullptr);
}



}}





