#include"oat_icon.hpp"
#include<algorithm>




namespace oat{




Icon::
Icon(std::initializer_list<const IconModule*>  ls):
modules(ls),
current(0),
callback(nullptr)
{
  change_content_width( IconModule::size);
  change_content_height(IconModule::size);
}




const IconModule&
Icon::
get_module(int  i) const
{
  return *modules[i];
}


void
Icon::
change_current(int  i)
{
    if(current != i)
    {
      current = i;

      need_to_redraw();
    }
}


const int&
Icon::
get_current() const
{
  return current;
}


void
Icon::
set_callback(Callback  cb)
{
  callback = cb;
}


void
Icon::
process_mouse(const Mouse&  mouse)
{
    if(callback)
    {
      callback(*this);
    }
}


void
Icon::
render()
{
    if(modules.empty())
    {
      return;
    }


  auto  pt = content.point;

  const IconModule&  m = *modules[current];

    for(int  y = 0;  y < IconModule::size;  ++y){
    for(int  x = 0;  x < IconModule::size;  ++x){
      auto  c = palette::get_color(m.map[y][x]);

        if(c)
        {
          draw_dot(*c,pt.x+x,pt.y+y);
        }
    }}
}




}




