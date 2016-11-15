#ifndef MG_MOTION_SELECTOR_HPP_INCLUDED
#define MG_MOTION_SELECTOR_HPP_INCLUDED


#include"oat.hpp"
#include"mg_core.hpp"




class
MotionSelector: public oat::Widget
{
public:
  MotionSelector();

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};



#endif




