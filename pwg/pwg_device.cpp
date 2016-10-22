#include"pwg_device.hpp"
#include<limits>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cctype>




namespace pwg{




Device::
Device(sample_t  v, bool  m):
play_counter(0),
rest_counter(0),
base_volume(v),
active_volume(v),
running(false),
muted(m)
{
}




bool
Device::
is_running() const
{
  return running;
}


bool
Device::
is_muted() const
{
  return muted;
}


void    Device::mute(){muted =  true;}
void  Device::unmute(){muted = false;}


void  Device::start(){running =  true;}
void  Device::stop(){ running = false;}


void  Device::reset_play_counter(uint32_t  n){play_counter = n;}
void  Device::reset_rest_counter(uint32_t  n){rest_counter = n;}

uint32_t  Device::get_play_counter() const{return play_counter;}
uint32_t  Device::get_rest_counter() const{return rest_counter;}


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




void
Device::
skip_spaces(const char*&  p)
{
    while(isspace(*p))
    {
      p += 1;
    }
}


int
Device::
skip_comment(const char*&  p)
{
  const char*  start = p;

    if(*p == '%')
    {
      p += 1;

        while(*p)
        {
            if(*p == '\n')
            {
              p += 1;

              break;
            }


          p += 1;
        }
    }


  return p-start;
}




}




