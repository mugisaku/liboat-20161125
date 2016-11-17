#include"mg_motionselector.hpp"
#include"mg_colorselector.hpp"
#include"mg_core.hpp"




using namespace oat;


MotionSelector::
MotionSelector()
{
  change_content_width( core::get_chip_width()*core::get_chip_number());
  change_content_height(core::get_chip_height());

  style.background_color = const_color::blue;
}




void
MotionSelector::
process_mouse(const Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressing())
    {
      core::change_chip_index(pt.x/core::get_chip_width());
    }
}


void
MotionSelector::
render()
{
  fill();


  auto  pt = content.point;

  auto  w = core::get_chip_width()*core::get_chip_number();

    for(int  y = 0;  y < core::get_chip_height();  ++y){
    for(int  x = 0;  x < w;                        ++x){
      auto  v = core::get_frame_pixel(x,y);

        if(v&8)
        {
          draw_dot(::palette[v&7],pt.x+x,pt.y+y);
        }
    }}


  auto  x_base = core::get_chip_width()*core::get_chip_index();

  draw_rect(const_color::white,pt.x+x_base,
                               pt.y,core::get_chip_width(),core::get_chip_height());
}




