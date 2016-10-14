#include"fcfont_colorselector.hpp"


using namespace oat;


namespace fcfont{


ColorSelector::
ColorSelector():
current(0)
{
  style.background_color = const_color::black;

  change_content_width( pixel_size*4);
  change_content_height(pixel_size);
}




int
ColorSelector::
get() const
{
  return current;
}


void
ColorSelector::
process_mouse(const Mouse&  mouse)
{
    if(mouse.left.test_pressing())
    {
      current = get_mouse_point(mouse).x/pixel_size;

      need_to_redraw();
    }
}


void
ColorSelector::
render()
{
  auto  pt = content.point;

  fill();

    for(int  x = 0;  x < 4;  ++x)
    {
      fill_rect(Character::color_table[x],pt.x+(pixel_size*x),pt.y,pixel_size,pixel_size);
    }


  draw_rect(const_color::red ,pt.x+(pixel_size*current)  ,pt.y  ,pixel_size  ,pixel_size  );
  draw_rect(const_color::blue,pt.x+(pixel_size*current)+1,pt.y+1,pixel_size-2,pixel_size-2);
}



}




