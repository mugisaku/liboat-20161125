#include"pwg_device.hpp"
#include<limits>
#include<cmath>
#include<cstdio>




namespace pwg{




Device::
Device(sample_t  v, bool  m):
base_volume(v),
active_volume(v),
muted(m)
{
}


void
Device::
advance()
{
}




bool
Device::
is_muted() const
{
  return muted;
}


void    Device::mute(){muted =  true;}
void  Device::unmute(){muted = false;}


sample_t    Device::get_base_volume() const{return base_volume;}
sample_t  Device::get_active_volume() const{return active_volume;}

void  Device::change_base_volume(sample_t  v){base_volume = v;}
void  Device::change_active_volume(sample_t  v){active_volume = v;}




sample_t
Device::
get_sample() const
{
  return silence;
}




sample_t
Device::
silence;


void
Device::
change_silence(sample_t  v)
{
  silence = v;
}


sample_t
Device::
get_silence()
{
  return silence;
}


}




