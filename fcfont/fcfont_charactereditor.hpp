#ifndef FCFONT_CHARACTEREDITOR_HPP_INCLUDED
#define FCFONT_CHARACTEREDITOR_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


struct CharacterSelector;
struct CombinedSelector;


class
CharacterEditor: public Widget
{
  static constexpr int  pixel_size = 10;

  Point  cursor;

  CharacterSelector&  chrsel;
  CombinedSelector&   cmbsel;

public:
  CharacterEditor(CharacterSelector&  chrsel_, CombinedSelector&  cmbsel_);

  void  process_mouse(const Mouse&  mouse) override;
  void  render() override;

};


}




#endif




