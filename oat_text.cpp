#include"oat_text.hpp"
#include"oat_font.hpp"




namespace oat{




Text::
Text(const std::string&  s):
callback(nullptr)
{
  change_content_height(font::height);

  change_string(s);
}


Text::
Text(const std::u16string&  s):
callback(nullptr)
{
  change_content_height(font::height);

  change_string(s);
}




void
Text::
change_string(const std::string&  s)
{
  u16string.clear();

  string = s;

  change_content_width(font::width*s.size());

  need_to_redraw();
}


void
Text::
change_string(const std::u16string&  s)
{
  string.clear();

  u16string = s;

  change_content_width(font::width*s.size());

  need_to_redraw();
}


const std::string&
Text::
get_string() const
{
  return string;
}


const std::u16string&
Text::
get_u16string() const
{
  return u16string;
}




void
Text::
render()
{
  auto  base = content.point;

  fill();

       if(   string.size()){draw_text(style.font_color,   string,base.x,base.y);}
  else if(u16string.size()){draw_text(style.font_color,u16string,base.x,base.y);}
}


}




