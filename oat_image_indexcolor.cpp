#include"oat_image.hpp"




namespace oat{




IndexColorImage::
IndexColorImage()
{
}


IndexColorImage::
IndexColorImage(IndexColorImageModule&&  m, int  pixel_size_, int  view_w, int  view_h):
Image(pixel_size_,view_w,view_h)
{
  reset_module(std::move(m));
}




      IndexColorImageModule&  IndexColorImage::get_module()            {return module;}
const IndexColorImageModule&  IndexColorImage::get_const_module() const{return module;}


void
IndexColorImage::
clear()
{
  module.fill(0);
}


void
IndexColorImage::
reset_module(IndexColorImageModule&&  m)
{
  module = std::move(m);

    if(!view_width ){view_width  = module.get_width() ;}
    if(!view_height){view_height = module.get_height();}


  change_content_width (pixel_size*view_width );
  change_content_height(pixel_size*view_height);

  need_to_redraw();
}


const Color&
IndexColorImage::
get_color(int  x, int  y) const
{
  auto  res = palette::get_color(get_index(x,y));

  return res? *res:style.background_color;
}


palette::index_t&
IndexColorImage::
get_index(int  x, int  y) const
{
  return module.get_element(x,y);
}


}




