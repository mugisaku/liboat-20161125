#ifndef MG_PATTERN_DISPLAY_HPP_INCLUDED
#define MG_PATTERN_DISPLAY_HPP_INCLUDED


#include"oat.hpp"




class
PatternDisplay: public oat::Widget
{
public:
  PatternDisplay();

  void  process_mouse(const oat::Mouse&  mouse) override;

  void  render() override;

};





#endif




