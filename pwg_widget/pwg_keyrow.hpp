#ifndef PWG_KEYROW_HPP_INCLUDED
#define PWG_KEYROW_HPP_INCLUDED


#include<SDL.h>
#include<list>
#include"oat.hpp"
#include"pwg/pwg_wavedevice.hpp"




namespace pwg{


struct Keyboard;

struct
Key
{
  Keyboard&  board;

  oat::Button*  button;

  WaveDevice  device;

  Key(Keyboard&  brd, const char16_t*  text, WaveKind  k, double  f, sample_t  v):
  board(brd),
  button(new oat::Button(new oat::Text(text))),
  device(k,f,v){}

};


class
KeyRow
{
  Key*  keys[8];

public:
  KeyRow(Keyboard&  brd, WaveKind  k);

  Key*  get_key(int  i) const;

  oat::TableRow*  create_table(const char16_t*  text);

};


}


#endif




