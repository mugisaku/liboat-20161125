#include"pwg_wavedevice.hpp"
#include<limits>
#include<cmath>
#include<cstdio>
#include<cctype>




namespace pwg{




constexpr double  pi = 3.1415926535897932384626433832795;




WaveDevice::
WaveDevice(WaveKind  k):
wave_kind(k),
frequency(0.0),
fullwidth(0),
halfwidth(0),
variation(0),
stream_time(0),
note_index(0),
callback(nullptr)
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
set_callback(Callback  cb)
{
  callback = cb;
}


void
WaveDevice::
append_note(const char*  s)
{
    for(;;)
    {
      Note  tmp;

      tmp.rest_flag  = false;

        while(isspace(*s))
        {
          s += 1;
        }


        if(!*s)
        {
          break;
        }


      char  c = *s++;

      char  marks[8] = {0};

      int  staccato = 0;

      int  i =  0;
      int  l = 16;
      int  n =  0;

        if(sscanf(s,"%8[<>+-*/.]%n",marks,&n) == 1)
        {
          s += n;
        }


        switch(c)
        {
      case('c'):        ;break;
      case('d'): i +=  2;break;
      case('e'): i +=  4;break;
      case('f'): i +=  5;break;
      case('g'): i +=  7;break;
      case('a'): i +=  9;break;
      case('b'): i += 11;break;
      case('z'): tmp.rest_flag = true;break;

      default:
          printf("%cは不正な文字です\n",c);
          return;
        }


        for(const char*  it = marks;  *it;  ++it)
        {
            switch(*it)
            {
          case('<'): i -= 12;break;
          case('>'): i += 12;break;
          case('+'): i +=  1;break;
          case('-'): i -=  1;break;
          case('*'): l *=  2;break;
          case('/'): l /=  2;break;
          case('.'): staccato += 1;break;
          case(' '): break;

          default:
              printf("%cは不正な文字です\n",c);
              return;
            }
        }


      tmp.frequency = get_scale_frequency(i);

      tmp.counter = sample_rate*2/64*l;

        if(staccato)
        {
          tmp.counter /= 2*staccato;
        }


      note_list.emplace_back(tmp);

        if(staccato)
        {
          tmp.rest_flag = true;

          note_list.emplace_back(tmp);
        }
    }
}


void
WaveDevice::
clear_note()
{
  note_index = 0;

  note_list.clear();
}


void
WaveDevice::
rewind_step()
{
  note_index = 0;

  step();
}


void
WaveDevice::
step()
{
    if(note_index < note_list.size())
    {
      note = note_list[note_index++];

      change_frequency(note.frequency);
    }

  else
    {
      stop();

        if(callback)
        {
          callback();
        }
    }
}




void
WaveDevice::
advance()
{
  stream_time += 1;

    if(note.counter)
    {
      note.counter -= 1;

        if(!note.counter)
        {
          step();
        }
    }
}




sample_t
WaveDevice::
get_sample() const
{
    if(muted || !running || (note.rest_flag && note.counter))
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




