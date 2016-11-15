#ifndef MG_CANVAS_HPP_INCLUDED
#define MG_CANVAS_HPP_INCLUDED


#include"oat.hpp"




class
Canvas: public oat::Widget
{
  const bool  grid_extent;

public:
  Canvas(bool  grid_extent_=false);

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};




#endif




