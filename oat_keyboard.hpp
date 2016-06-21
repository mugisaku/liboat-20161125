#ifndef OAT_KEYBOARD_HPP
#define OAT_KEYBOARD_HPP


#include"oat_buttonmodule.hpp"


namespace oat{


struct
Keyboard
{
  ButtonModule   left;
  ButtonModule  right;
  ButtonModule   down;
  ButtonModule     up;

  ButtonModule  shift;
  ButtonModule  space;
  ButtonModule  advance;
  ButtonModule  back;

};


}




#endif




