#include"pwg_noisedevice.hpp"
#include<limits>
#include<cmath>
#include<cstdio>




namespace pwg{




NoiseDevice::
NoiseDevice()
{
  rewind();
}


NoiseDevice::
NoiseDevice(sample_t  v, bool  muted_):
Device(v,muted_)
{
  rewind();
}




void
NoiseDevice::
advance()
{
  seed = seed ^ (seed << 13);
  seed = seed ^ (seed >> 17);
  seed = seed ^ (seed <<  5);
}


void
NoiseDevice::
rewind()
{
  seed = 1234567890;
}


void
NoiseDevice::
read_score(const char*&  s)
{
}


void
NoiseDevice::
clear_score()
{
}


sample_t
NoiseDevice::
get_sample() const
{
    if(muted || !running)
    {
      return silence;
    }


  return (((seed&0xFFFF)<<16)/sample_max*active_volume)>>16;
}




}




