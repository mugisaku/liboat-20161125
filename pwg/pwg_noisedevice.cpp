#include"pwg_noisedevice.hpp"
#include<limits>
#include<cmath>
#include<cstdio>




namespace pwg{




NoiseDevice::
NoiseDevice(sample_t  v, bool  muted_):
Device(v,muted_),
seed(12345678)
{
}




void
NoiseDevice::
advance()
{
  seed = seed ^ (seed << 13);
  seed = seed ^ (seed >> 17);
  seed = seed ^ (seed <<  5);
}




sample_t
NoiseDevice::
get_sample() const
{
    if(muted || !running)
    {
      return silence;
    }


  return ((seed*65536)/sample_max*active_volume)/65536;
}




}




