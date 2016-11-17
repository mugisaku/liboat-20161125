#include"mg_framepositioner.hpp"
#include"mg_colorselector.hpp"
#include"mg_core.hpp"




using namespace oat;


FramePositioner::
FramePositioner()
{
  change_content_width( core::image_size);
  change_content_height(core::image_size);

  style.background_color = const_color::blue;
}




void
FramePositioner::
process_mouse(const Mouse&  mouse)
{
  const int  w = core::get_chip_width()*core::get_chip_number();
  const int  h = core::get_chip_height();

  cursor = get_mouse_point(mouse);

    if((cursor.x+w) >= core::image_size)
    {
      cursor.x = core::image_size-w;
    }

  else
    {
      cursor.x /= w;
      cursor.x *= w;
    }


    if((cursor.y+h) >= core::image_size)
    {
      cursor.y = core::image_size-h;
    }

  else
    {
      cursor.y /= h;
      cursor.y *= h;
    }


    if(mouse.left.test_pressing())
    {
      core::change_frame_point(cursor);
    }


  need_to_redraw();
}


void
FramePositioner::
render()
{
  fill();


  auto  pt = content.point;

  auto  w = core::get_chip_width()*core::get_chip_number();

    for(int  y = 0;  y < core::image_size;  ++y){
    for(int  x = 0;  x < core::image_size;  ++x){
      auto  v = core::get_image_pixel(x,y);

        if(v&8)
        {
          draw_dot(::palette[v&7],pt.x+x,pt.y+y);
        }
    }}


  auto&  frm = core::get_frame();

  draw_rect(const_color::white,pt.x+frm.x,
                               pt.y+frm.y,frm.w,frm.h);

  draw_rect(const_color::black,pt.x+frm.x+1,
                               pt.y+frm.y+1,frm.w-2,frm.h-2);


  draw_rect(const_color::red,pt.x+cursor.x+1,
                             pt.y+cursor.y+1,frm.w-2,frm.h-2);
}




