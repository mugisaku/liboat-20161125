#ifndef MG_PATTERN_TABLE_HPP_INCLUDED
#define MG_PATTERN_TABLE_HPP_INCLUDED


#include"mg_core.hpp"
#include"oat.hpp"




class
PatternTable
{
public:
  static constexpr int  size = 3;

private:
  oat::Point  data[size][size];

public:
  void                change(int  x, int  y)      ;
  const oat::Point&      get(int  x, int  y) const;

};



#endif




