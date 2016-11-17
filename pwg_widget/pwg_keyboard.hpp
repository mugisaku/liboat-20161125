#ifndef PWG_KEYBOARD_HPP_INCLUDED
#define PWG_KEYBOARD_HPP_INCLUDED


#include"pwg_keyrow.hpp"
#include"pwg/pwg_noisedevice.hpp"
#include<SDL.h>




namespace pwg{




struct Monitor;


class
Keyboard: public oat::Container
{
  KeyRow      sine_keyrow;
  KeyRow    square_keyrow;
  KeyRow  triangle_keyrow;
  KeyRow  sawtooth_keyrow;

  NoiseDevice  noise;

  std::list<Key*>  active_key_list;

public:
  Keyboard();

  Key*  get_key(SDL_Keycode  kode);

  void  push(Key*  k);

  void     press(SDL_Keycode  kode);
  void   unpress(SDL_Keycode  kode);

  void  output(sample_t*  dst, const sample_t*  dst_end, Monitor*  mon=nullptr);

};


}


#endif




