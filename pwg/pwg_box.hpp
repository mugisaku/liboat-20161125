#ifndef PWG_BOX_HPP_INCLUDED
#define PWG_BOX_HPP_INCLUDED


#include"pwg_wave.hpp"
#include"pwg_device.hpp"
#include"pwg_wavedevice.hpp"
#include"pwg_noisedevice.hpp"
#include<list>




namespace pwg{


struct
Box
{
  std::list<Device*>  device_list;

  uint32_t  active_device_number;

  using Callback = void  (*)();

  int  finished;

  Callback  finish;

   Box();
  ~Box();

  void  clear();

  void  ready();

  void  load(const char*  path);
  void  save(const char*  path);

  void  mix(sample_t*  dst, const sample_t*  const dst_end);

};


}


#endif




