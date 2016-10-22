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

  uint32_t  play_counter;
  uint32_t  rest_counter;

  sample_t    base_volume;
  sample_t  active_volume;

  bool  running;
  bool    muted;

public:
  Device(sample_t  v=0, bool m=true);

 virtual ~Device(){}


  bool  is_running() const;
  bool  is_muted() const;

  void    mute();
  void  unmute();

  void  start();
  void   stop();

  void  reset_play_counter(uint32_t  n);
  void  reset_rest_counter(uint32_t  n);

  uint32_t  get_play_counter() const;
  uint32_t  get_rest_counter() const;

  sample_t    get_base_volume() const;
  sample_t  get_active_volume() const;

  void  change_base_volume(sample_t  v);
  void  change_active_volume(sample_t  v);

  virtual void  advance()=0;
  virtual void   rewind()=0;

  virtual sample_t  get_sample() const=0;

  virtual void  read_score(const char*&  s)=0;
  virtual void  clear_score()=0;

  static void  change_silence(sample_t  v);
  static sample_t  get_silence();

  static void  skip_spaces(const char*&  p);
  static int  skip_comment(const char*&  p);

};


}


#endif




