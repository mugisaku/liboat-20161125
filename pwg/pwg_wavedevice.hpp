#ifndef PWG_WAVEDEVICE_HPP_INCLUDED
#define PWG_WAVEDEVICE_HPP_INCLUDED


#include"pwg_device.hpp"
#include<vector>




namespace pwg{




enum class
WaveKind
{
  square,
  triangle,
  sawtooth,
  sine,

};


struct
Note
{
  double  frequency;

  uint32_t  play_counter=0;
  uint32_t  rest_counter=0;

};


class
WaveDevice: public Device
{
public:
  using Callback = void (*)();

private:
  WaveKind  wave_kind;

  double  frequency;

  uint32_t  fullwidth;
  uint32_t  halfwidth;
  uint32_t  variation;

  uint32_t  stream_time;

  std::vector<Note>  note_list;

  uint32_t  note_index;

  Callback  callback;

public:
  WaveDevice(WaveKind  k=WaveKind::square);
  WaveDevice(WaveKind  k, double  f, sample_t  v, bool  muted_=true);

  void  change_wave_kind(WaveKind  k);
  void  change_frequency(double  f);

  void  reset(double  f, sample_t  v, bool  muted_=true);

  void  set_callback(Callback  cb);

  void  read_score(const char*&  s) override;
  void  clear_score() override;

  void  rewind() override;

  void  advance() override;

  sample_t  get_sample() const override;

};


}


#endif




