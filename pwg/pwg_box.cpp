#include"pwg_box.hpp"
#include<cstdio>
#include<string>




namespace pwg{




Box::
Box():
active_device_number(0),
finish(nullptr)
{
}


Box::
~Box()
{
  clear();
}




void
Box::
clear()
{
    for(auto  ptr: device_list)
    {
      delete ptr;
    }


  device_list.clear();
}


void
Box::
ready()
{
  finished = 0;

    for(auto  ptr: device_list)
    {
      ptr->unmute();
      ptr->rewind();
      ptr->start();
    }
}




namespace{
std::string
load_file(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(!f)
    {
      printf("%sを開けませんでした\n",path);

      throw path;
    }


  std::string  s;

    for(;;)
    {
      int  c = fgetc(f);

        if(feof(f))
        {
          break;
        }


      s.push_back(c);
    }


  fclose(f);


  return std::move(s);
}


std::string
scan_id(const char*&  s)
{
  std::string  id;

  Device::skip_spaces(s);

    if(isalpha(*s))
    {
      id.push_back(*s++);
    }


    while(isalnum(*s))
    {
      id.push_back(*s++);
    }


  return std::move(id);
}


}


void
Box::
load(const char*  path)
{
  auto  s = load_file(path);

  auto  p = s.data();

    while(*p)
    {
      auto  id = scan_id(p);

      Device*  dev = nullptr;

           if(id == "square"  ){dev = new WaveDevice(WaveKind::square  );}
      else if(id == "sine"    ){dev = new WaveDevice(WaveKind::sine    );}
      else if(id == "triangle"){dev = new WaveDevice(WaveKind::triangle);}
      else if(id == "sawtooth"){dev = new WaveDevice(WaveKind::sawtooth);}
      else if(id == "noise"   ){dev = new NoiseDevice;}
      else
        {
          printf("%sは不明なデバイスです\n",id.data());

          throw id;
        }


      dev->change_active_volume(2400);

      device_list.emplace_back(dev);

      Device::skip_spaces(p);

        if(*p == '{')
        {
          p += 1;

          dev->read_score(p);
        }


      Device::skip_spaces(p);
    }
}


void
Box::
save(const char*  path)
{
  Wave  wav(path);

    for(auto  ptr: device_list)
    {
      ptr->unmute();

      ptr->start();
    }


    for(;;)
    {
      int  v = Device::get_silence();

      int  n = 0;

        for(auto  ptr: device_list)
        {
            if(ptr->is_running())
            {
              n += 1;

              v += ptr->get_sample();

              ptr->advance();
            }
        }


        if(!n)
        {
          break;
        }


      wav.fput16le(clamp(v));
    }
}




void
Box::
mix(sample_t*  dst, const sample_t*  const dst_end)
{
  active_device_number = 0;

    for(auto  dev: device_list)
    {
        if(dev->is_running())
        {
          active_device_number += 1;
        }
    }


    if(!active_device_number)
    {
        if(!finished)
        {
            if(finish)
            {
              finish();
            }


          finished = 1;
        }
    }


    while(dst < dst_end)
    {
      int  v = Device::get_silence();

        if(active_device_number)
        {
            for(auto  dev: device_list)
            {
              v += dev->get_sample();
     
              dev->advance();
            }
        }


      *dst++ = clamp(v);
    }
}




}




