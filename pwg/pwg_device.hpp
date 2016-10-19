#ifndef PWG_DEVICE_HPP_INCLUDED
#define PWG_DEVICE_HPP_INCLUDED


#include<cstdint>
#include<cstddef>
#include<limits>




namespace pwg{




static const int  sample_rate = 16000;

using sample_t = uint16_t;

constexpr sample_t  sample_max = std::numeric_limits<sample_t>::max();
constexpr sample_t  sample_min = std::numeric_limits<sample_t>::min();


constexpr sample_t
clamp(int  v)
{
  return((v >= sample_max)? sample_max:
         (v <= sample_min)? sample_min:v);
}


double  get_scale_frequency(int  offset);


class
Device
{
protected:
  static sample_t  silence;

  sample_t    base_volume;
  sample_t  active_volume;

  bool  muted;

public:
  Device(sample_t  v=0, bool m=true);

  bool  is_muted() const;

  void    mute();
  void  unmute();

  sample_t    get_base_volume() const;
  sample_t  get_active_volume() const;

  void  change_base_volume(sample_t  v);
  void  change_active_volume(sample_t  v);

  virtual void  advance();

  virtual sample_t  get_sample() const;

  static void  change_silence(sample_t  v);
  static sample_t  get_silence();

};


}


#endif




