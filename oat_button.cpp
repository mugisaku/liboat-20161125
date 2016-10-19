#include"oat_button.hpp"
#include"oat_font.hpp"
#include"oat.hpp"




namespace oat{




Button::
Button(Text*  text):
callback(nullptr)
{
  children.emplace_back(nullptr);
  icon_ptr = &children.back();

  children.emplace_back(nullptr);
  text_ptr = &children.back();

  change_content_width( font::width );
  change_content_height(font::height);

  change_text(text);
}


Button::
Button(Icon*  icon, Text*  text):
callback(nullptr)
{
  children.emplace_back(nullptr);
  icon_ptr = &children.back();

  children.emplace_back(nullptr);
  text_ptr = &children.back();

  change_content_width( font::width );
  change_content_height(font::height);

  change_icon(icon);
  change_text(text);
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
change_icon(Icon*  icon)
{
  delete *icon_ptr       ;
         *icon_ptr = icon;

    if(icon)
    {
      icon->update_sizes();

      change_content_width( icon->width +4);
      change_content_height(icon->height+4);

      rejoin(*icon,2,2);

      need_to_reform();
      need_to_redraw();
    }
}


void
Button::
change_text(Text*  text)
{
  delete *text_ptr       ;
         *text_ptr = text;

    if(text)
    {
      auto  icon = *icon_ptr;

      int  w = 0;
      int  h = 0;

        if(icon)
        {
          icon->update_sizes();

          w = icon->width ;
          h = icon->height;
        }


      text->update_sizes();

      w = std::max(w,text->width );
      h = std::max(h,text->height);

      w += 8;
      h += 8;

      change_content_width( w);
      change_content_height(h);

      rejoin(*text,icon? icon->width+4:4,4);

      need_to_reform();
      need_to_redraw();
    }
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
  auto  pt = content.point;

    if(module.test_pressing()){draw_concave_rect(style.background_color,pt.x,pt.y,content.width,content.height);}
  else                        {draw_convex_rect( style.background_color,pt.x,pt.y,content.width,content.height);}

    for(auto  child: children)
    {
        if(child)
        {
          child->render();
        }
    }
}




}




