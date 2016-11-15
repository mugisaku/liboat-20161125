#include"aicone_canvas.hpp"
#include"oat.hpp"




namespace oat{




void
Canvas::
reverse_horizontally()
{
  auto  tmp = module;

  const int  w = module.get_width() ;
  const int  h = module.get_height();

    for(int  y = 0;  y < h;  ++y){
    for(int  x = 0;  x < w;  ++x){
      get_index(x,y) = tmp.get_element(x,h-y-1);
    }}


  need_to_redraw();
}


void
Canvas::
reverse_vertically()
{
  auto  tmp = module;

  const int  w = module.get_width() ;
  const int  h = module.get_height();

    for(int  y = 0;  y < h;  ++y){
    for(int  x = 0;  x < w;  ++x){
      get_index(x,y) = tmp.get_element(w-x-1,y);
    }}


  need_to_redraw();
}


void
Canvas::
revolve()
{
  auto  tmp = module;

  const int  w = std::min(module.get_width(),module.get_height());

    for(int  y = 0;  y < w;  ++y){
    for(int  x = 0;  x < w;  ++x){
      get_index(w-y-1,x) = tmp.get_element(x,y);
    }}


  need_to_redraw();
}




}




