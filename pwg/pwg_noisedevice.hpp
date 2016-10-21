#ifndef PWG_NOISEDEVICE_HPP_INCLUDED
#define PWG_NOISEDEVICE_HPP_INCLUDED


#include"pwg_device.hpp"




namespace pwg{




class
NoiseDevice: public Device
{
  uint32_t  seed;

public:
  NoiseDevice();
  NoiseDevice(sample_t  v, bool  muted_=true);

  void  reset();
  void  reset(double  f, sample_t  v, bool  muted_=true);

  void  advance() override;

  void  read_score(const char*&  s) override;

  void  clear_score() override;

  void  rewind() override;

  sample_t  get_sample() const override;

};


}


#endif




