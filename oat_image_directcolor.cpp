#include"oat_image.hpp"




namespace oat{




DirectColorImage::
DirectColorImage()
{
}


DirectColorImage::
DirectColorImage(DirectColorImageModule&&  m, int  pixel_size_, int  view_w, int  view_h):
Image(pixel_size_,view_w,view_h)
{
  reset_module(std::move(m));
}

      DirectColorImageModule&  DirectColorImage::get_module()            {return module;}
const DirectColorImageModule&  DirectColorImage::get_const_module() const{return module;}


void
DirectColorImage::
clear()
{
  module.fill(style.background_color);
}


void
DirectColorImage::
reset_module(DirectColorImageModule&&  m)
{
  module = std::move(m);

    if(!view_width ){view_width  = module.get_width() ;}
    if(!view_height){view_height = module.get_height();}


  change_content_width (pixel_size*view_width );
  change_content_height(pixel_size*view_height);

  need_to_redraw();
}




Color&
DirectColorImage::
get_color(int  x, int  y)
{
  return module.get_element(x,y);
}


const Color&
DirectColorImage::
get_color(int  x, int  y) const
{
  return module.get_element(x,y);
}


}




