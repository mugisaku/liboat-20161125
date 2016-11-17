#ifndef FCFONT_EDITOR_HPP_INCLUDED
#define FCFONT_EDITOR_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


struct ColorSelector;
struct CharacterSelector;
struct CharacterEditor;
struct CombinedSelector;
struct Sample;


class
Editor: public Container
{
  CharacterSelector*  chr_selector;
  CharacterEditor*      chr_editor;

  CombinedSelector*  cmb_selector;
  ColorSelector*  col_selector;

  Sample*  sample;

  Text*  chr_cp_text;
  Text*  cmb_cp_text;

  Button*    chr_up_button;
  Button*  chr_down_button;
  Button*    cmb_up_button;
  Button*  cmb_down_button;

  Button*  upper_button;
  Button*  lower_button;

  Button*  save_button;

  static void    chr_up(Button&  btn);
  static void  chr_down(Button&  btn);
  static void    cmb_up(Button&  btn);
  static void  cmb_down(Button&  btn);

  static void  chr_update(void*  ptr);
  static void  cmb_update(void*  ptr);

  static void  change_upper(Button&  btn);
  static void  change_lower(Button&  btn);

public:
  Editor();

};


}




#endif




