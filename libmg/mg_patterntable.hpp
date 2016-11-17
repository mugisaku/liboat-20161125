#ifndef MG_PATTERN_TABLE_HPP_INCLUDED
#define MG_PATTERN_TABLE_HPP_INCLUDED


#include"mg_core.hpp"
#include"oat.hpp"




namespace pattern_table{


constexpr int  size = 3;


void                change(int  x, int  y);
const oat::Point&      get(int  x, int  y);


}



#endif




