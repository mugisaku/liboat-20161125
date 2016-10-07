#ifndef FCFONT_SAMPLE_HPP_INCLUDED
#define FCFONT_SAMPLE_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


class
Sample: public Widget
{
  static constexpr int  x_element_number = 32;
  static constexpr int  y_element_number =  6;

  char16_t  unicode;

public:
  Sample();

  void  change(char16_t  unicode_);

  void  render() override;

};


}


#endif




