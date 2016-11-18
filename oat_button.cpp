#include"oat_button.hpp"
#include"oat_font.hpp"
#include"oat.hpp"




namespace oat{




Button::
Button(Widget*  child, Callback  cb):
callback(cb)
{
  style.top_margin    = 4;
  style.left_margin   = 4;
  style.right_margin  = 4;
  style.bottom_margin = 4;

  change_child(child);
}




const ButtonModule*
Button::
operator->() const
{
  return &module;
}


ButtonModule&
Button::
get_module()
{
  return module;
}


const ButtonModule&
Button::
get_const_module() const
{
  return module;
}


void
Button::
change_child(Widget*  child)
{
    if(children.size())
    {
      delete children.front();

      children.clear();
    }


  join(child,0,0);

  need_to_reform();
  need_to_redraw();
}


void
Button::
set_callback(Callback  cb, bool  repeat)
{
  callback = cb;
}


void
Button::
press()
{
  module.press();

    if(callback)
    {
      callback(*this);
    }


  need_to_redraw();
}


void
Button::
unpress()
{
  module.unpress();

    if(callback)
    {
      callback(*this);
    }


  need_to_redraw();
}


void
Button::
process_mouse(const Mouse&  mouse)
{
  bool  flag = false;

       if(mouse.left.test_pressed()  ){  press();}
  else if(mouse.left.test_unpressed()){unpress();}
}


void
Button::
process_when_mouse_left()
{
  module.unpress();

    if(callback)
    {
      callback(*this);
    }


  need_to_redraw();
}




void
Button::
render()
{
    if(module.test_pressing()){draw_concave_rect(style.background_color,point.x,point.y,width-2,height-2);}
  else                        {draw_convex_rect( style.background_color,point.x,point.y,width-2,height-2);}

  Container::render();
}




}




