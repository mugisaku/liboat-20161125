#include"mg_colorselector.hpp"
#include"mg_core.hpp"




using namespace oat;


constexpr int   frame_size = 20;
constexpr int  square_size = 16;


ColorSelector::
ColorSelector()
{
  change_content_width( frame_size*color_number/2);
  change_content_height(frame_size*2);
}




void
ColorSelector::
process_mouse(const Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressing())
    {
      int  v = (pt.x/frame_size)<<1;

      v |= ((pt.y < frame_size)? 0:1);


      core::change_color_index(v);
    }
}


void
ColorSelector::
render()
{
  fill();


  auto  pt = content.point;

  const Color*  color = ::palette;

    for(int  x = 0;  x < color_number/2;  ++x)
    {
      fill_rect(*color++,pt.x+(frame_size*x),pt.y,square_size,square_size);
      fill_rect(*color++,pt.x+(frame_size*x),pt.y+frame_size,square_size,square_size);
    }


  auto  v = core::get_color_index();

  draw_rect(const_color::white,pt.x+(frame_size*(v>>1)),
                               pt.y+(v&1? frame_size:0),frame_size,frame_size);
}




