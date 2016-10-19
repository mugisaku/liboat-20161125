#ifndef PWG_NOISEDEVICE_HPP_INCLUDED
#define PWG_NOISEDEVICE_HPP_INCLUDED


#include"pwg_device.hpp"




namespace pwg{




class
NoiseDevice: public Device
{
  uint32_t  seed;

public:
  NoiseDevice(sample_t  v, bool  muted_=true);

  void  reset();
  void  reset(double  f, sample_t  v, bool  muted_=true);

  void  advance() override;

  sample_t  get_sample() const override;

};


}


#endif




