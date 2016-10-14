#ifndef FCFONT_COLORSELECTOR_HPP_INCLUDED
#define FCFONT_COLORSELECTOR_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


struct CharacterSelector;
struct CombinedSelector;


class
ColorSelector: public Widget
{
  static constexpr int  pixel_size = 20;

  int  current;

public:
  ColorSelector();

  int  get() const;

  void  process_mouse(const Mouse&  mouse) override;
  void  render() override;

};


}




#endif




