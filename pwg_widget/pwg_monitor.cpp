#include"pwg_monitor.hpp"




namespace pwg{




Monitor::
Monitor()
{
  change_content_width(512);
  change_content_height(256);
}




void
Monitor::
push(sample_t  v)
{
  wave.emplace_back(v);
}


void
Monitor::
clear()
{
  wave.clear();
}


void
Monitor::
render()
{
  auto  pt = content.point;

  fill(oat::const_color::white);

    for(auto  v: wave)
    {
      v /= 64;

      int  y = (255-v);

        if(y < 0)
        {
          y = 0;
        }


        while(y < 255)
        {
          draw_dot(oat::const_color::black,pt.x,pt.y+y++);
        }


      pt.x += 1;
    }
}




}




