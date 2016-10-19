#ifndef PWG_WAVEDEVICE_HPP_INCLUDED
#define PWG_WAVEDEVICE_HPP_INCLUDED


#include"pwg_device.hpp"




namespace pwg{




enum class
WaveKind
{
  square,
  triangle,
  sawtooth,
  sine,

};


class
WaveDevice: public Device
{
  WaveKind  wave_kind;

  double  frequency;

  uint32_t  fullwidth;
  uint32_t  halfwidth;
  uint32_t  variation;

  uint32_t  stream_time;

public:
  WaveDevice(WaveKind  k=WaveKind::square);
  WaveDevice(WaveKind  k, double  f, sample_t  v, bool  muted_=true);

  void  change_wave_kind(WaveKind  k);
  void  change_frequency(double  f);

  void  reset();
  void  reset(double  f, sample_t  v, bool  muted_=true);

  void  advance() override;

  sample_t  get_sample() const override;

};


}


#endif




