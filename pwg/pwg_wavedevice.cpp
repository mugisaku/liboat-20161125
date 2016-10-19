#include"pwg_wavedevice.hpp"
#include<limits>
#include<cmath>
#include<cstdio>




namespace pwg{




constexpr double  pi = 3.1415926535897932384626433832795;




WaveDevice::
WaveDevice(WaveKind  k):
wave_kind(k),
frequency(0.0),
fullwidth(0),
halfwidth(0),
variation(0),
stream_time(0)
{
}


WaveDevice::
WaveDevice(WaveKind  k, double  f, sample_t  v, bool  muted_):
wave_kind(k)
{
  reset(f,v,muted_);
}




void
WaveDevice::
reset()
{
  stream_time = 0;
}


void
WaveDevice::
reset(double  f, sample_t  v, bool  muted_)
{
  change_frequency(f);

    base_volume = v;
  active_volume = v;

  stream_time = 0;

  muted = muted_;
}


void
WaveDevice::
change_wave_kind(WaveKind  k)
{
  wave_kind = k;
}


void
WaveDevice::
change_frequency(double  f)
{
  frequency = f;

  fullwidth = sample_rate/f  ;
  halfwidth = sample_rate/f/2;

    switch(wave_kind)
    {
  case(WaveKind::square):
      variation = sample_max/(sample_rate/f/2);
      break;
  case(WaveKind::triangle):
      variation = sample_max/(sample_rate/f/2);
      break;
  case(WaveKind::sawtooth):
      variation = sample_max/(sample_rate/f);
      break;
  case(WaveKind::sine):
      break;
    }
}


void
WaveDevice::
advance()
{
  stream_time += 1;
}




sample_t
WaveDevice::
get_sample() const
{
    if(muted)
    {
      return silence;
    }


  auto  wave_time = stream_time%fullwidth;

    switch(wave_kind)
    {
  case(WaveKind::square):
      return (wave_time < halfwidth)? active_volume
                                    : 0;
      break;
  case(WaveKind::triangle):
    {
      unsigned int  v = variation*wave_time;

        if(wave_time >= halfwidth)
        {
          v = (sample_max*2)-v;

            if(v > sample_max)
            {
              v = sample_max;
            }
        }


      return ((v<<16)/sample_max*active_volume)>>16;
    }
      break;
  case(WaveKind::sawtooth):
    {
      unsigned int  v = variation*wave_time;

      return ((v<<16)/sample_max*active_volume)>>16;
    }
      break;
  case(WaveKind::sine):
    {
      unsigned int  v = (sample_max/2)*std::sin(2*pi/fullwidth*wave_time)+(sample_max/2);

      return ((v<<16)/sample_max*active_volume)>>16;
    }
      break;
    }


  return silence;
}




}




