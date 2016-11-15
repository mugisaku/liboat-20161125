#ifndef MG_CS_HPP_INCLUDED
#define MG_CS_HPP_INCLUDED


#include"oat.hpp"
#include"mg_core.hpp"




constexpr int  color_number = 8;


const oat::Color
palette[color_number] =
{
  oat::Color(0x1F),
  oat::Color(0x3F),
  oat::Color(0x5F),
  oat::Color(0x7F),
  oat::Color(0x9F),
  oat::Color(0xBF),
  oat::Color(0xDF),
  oat::Color(0xFF),
};


class
ColorSelector: public oat::Widget
{
public:
  ColorSelector();

  void  process_mouse(const oat::Mouse&  mouse) override;
  void  render() override;

};



#endif




