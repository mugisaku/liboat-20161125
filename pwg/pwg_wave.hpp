#ifndef PWG_WAVE_HPP_INCLUDED
#define PWG_WAVE_HPP_INCLUDED


#include<cstdio>
#include<cstdint>




namespace pwg{


class
Wave
{
  FILE*  file;

  fpos_t  riff_size_pos;
  fpos_t  data_size_pos;

  long  header_size;

public:
  Wave(const char*  path);
 ~Wave();


  void  fput16le(uint16_t  i);
  void  fput32le(uint32_t  i);

  void  finish();

};


}




#endif




