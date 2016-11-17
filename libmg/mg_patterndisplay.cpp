#include"mg_patterndisplay.hpp"
#include"mg_patterntable.hpp"
#include"mg_colorselector.hpp"
#include"mg_core.hpp"




constexpr int  pixel_size = 2;




PatternDisplay::
PatternDisplay()
{
  change_content_width( core::get_chip_width() *pixel_size*pattern_table::size);
  change_content_height(core::get_chip_height()*pixel_size*pattern_table::size);

  style.background_color = oat::const_color::blue;
}




void
PatternDisplay::
process_mouse(const oat::Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  int  w = core::get_chip_width() *pixel_size;
  int  h = core::get_chip_height()*pixel_size;

  cursor.x /= w;
  cursor.y /= h;

    if(mouse.left.test_pressing())
    {
      pattern_table::change(cursor.x,cursor.y);
    }


  cursor.x *= w;
  cursor.y *= h;

  need_to_redraw();
}


void
PatternDisplay::
render()
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < pattern_table::size;  y += 1){
    for(int  x = 0;  x < pattern_table::size;  x += 1){
      auto&  ptnpt = pattern_table::get(x,y);

        for(int  yy = 0;  yy < core::get_chip_height();  yy += 1){
        for(int  xx = 0;  xx < core::get_chip_width() ;  xx += 1){
          auto  v = core::get_image_pixel(ptnpt.x+xx,ptnpt.y+yy);

            if(v&8)
            {
              fill_rect(::palette[v&7],pt.x+(core::get_chip_width() *pixel_size*x)+(pixel_size*xx),
                                       pt.y+(core::get_chip_height()*pixel_size*y)+(pixel_size*yy),pixel_size,pixel_size);
            }
        }}
    }}


  draw_rect(oat::const_color::white,pt.x+cursor.x,
                                    pt.y+cursor.y,
                                    (pixel_size*core::get_chip_width()),
                                    (pixel_size*core::get_chip_height()));
}




