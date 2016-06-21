#include"oat_image.hpp"




namespace oat{




Image::
Image(int  pixel_size_, int  view_w, int  view_h)
{
  change_pixel_size(pixel_size_);

  change_view_size(view_w,view_h);
}




void
Image::
update_size()
{
  change_content_width (pixel_size*view_width );
  change_content_height(pixel_size*view_height);

  need_to_redraw();
}


void
Image::
change_view_size(int  w, int  h)
{
  view_width  = w;
  view_height = h;

  update_size();
}


void
Image::
change_pixel_size(int  n)
{
  pixel_size = n;

  update_size();
}


const Point&
Image::
get_view_point() const
{
  return view_point;
}


void
Image::
render()
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < view_height;  ++y){
    for(int  x = 0;  x < view_width ;  ++x){
      auto&  pix = get_color(view_point.x+x,view_point.y+y);

      fill_rect(pix,
                pt.x+(pixel_size*x),
                pt.y+(pixel_size*y),
                pixel_size,
                pixel_size);
    }}
}




}




