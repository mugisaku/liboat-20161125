#ifndef MG_ANIMATIONDISPLAY_HPP_INCLUDED
#define MG_ANIMATIONDISPLAY_HPP_INCLUDED


#include"oat.hpp"




class
AnimationDisplay: public oat::Widget
{
  int  phase;

public:
  AnimationDisplay();

  void  check(uint32_t  now);

  void  render() override;

};





#endif




