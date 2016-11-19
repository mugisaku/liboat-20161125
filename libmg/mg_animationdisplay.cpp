#include"mg_animationdisplay.hpp"
#include"mg_colorselector.hpp"
#include"mg_core.hpp"




constexpr int  pixel_size = 4;




AnimationDisplay::
AnimationDisplay():
phase(0)
{
  change_content_width( core::get_chip_width() *pixel_size);
  change_content_height(core::get_chip_height()*pixel_size);
}




void
AnimationDisplay::
check(uint32_t  now)
{
  static uint32_t  last;

    if(now >= last+200)
    {
      last = now;

      phase += 1;

        if(phase >= 4)
        {
          phase = 0;
        }


      need_to_redraw();
    }
}


void
AnimationDisplay::
render()
{
  fill();

  auto  pt = content.point;

  static int  bases[] = {0,1,0,2};

  int  x_base = core::get_chip_width()*bases[phase];

    for(int  y = 0;  y < core::get_chip_height();  y += 1){
    for(int  x = 0;  x < core::get_chip_width() ;  x += 1){
      auto  v = core::get_frame_pixel(x_base+x,y);

        if(v&8)
        {
          fill_rect(::palette[v&7],pt.x+(pixel_size*x),
                                   pt.y+(pixel_size*y),pixel_size,pixel_size);
        }
    }}
}




