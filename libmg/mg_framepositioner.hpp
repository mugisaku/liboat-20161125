#ifndef MG_FRAME_POSITIONER_HPP_INCLUDED
#define MG_FRAME_POSITIONER_HPP_INCLUDED


#include"oat.hpp"
#include"mg_core.hpp"




class
FramePositioner: public oat::Widget
{
  oat::Point  cursor;

public:
  FramePositioner();

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};



#endif




