#include"fcfont_characterselector.hpp"
#include"fcfont_charactereditor.hpp"


using namespace oat;


namespace fcfont{


CharacterSelector::
CharacterSelector(Callback  cb):
callback(cb),
now(Character::embedded_table),
buffer(u"X U+XXXX"),
offset(0)
{
  style.background_color = const_color::black;

  change_content_width( element_width*x_element_number);
  change_content_height(element_width*y_element_number);
}




Character*
CharacterSelector::
get() const
{
  return now;
}


const char16_t*
CharacterSelector::
get_buffer() const
{
  return buffer;
}


void
CharacterSelector::
up()
{
  offset -= x_element_number*y_element_number;

    if(offset < 0)
    {
      offset = 0;
    }


  need_to_redraw();
}


void
CharacterSelector::
down()
{
  offset += x_element_number*y_element_number;

  need_to_redraw();
}


void
CharacterSelector::
process_mouse(const Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x = cursor.x/element_width*element_width;
  cursor.y = cursor.y/element_width*element_width;

    if(mouse.left.test_pressing())
    {
      int  x = cursor.x/element_width;
      int  y = cursor.y/element_width;

      unsigned int  i = offset+((y<<3)|x);

        if(i < Character::embedded_number)
        {
          now = &Character::embedded_table[i];


          buffer[0] = now->unicode;

          static const char16_t  c_table[] = u"0123456789ABCDEF";

          auto  p = &buffer[4];

          *p++ = c_table[(now->unicode>>12)&0xF];
          *p++ = c_table[(now->unicode>> 8)&0xF];
          *p++ = c_table[(now->unicode>> 4)&0xF];
          *p   = c_table[(now->unicode>> 0)&0xF];
        }


        if(callback)
        {
          callback(get_userdata());
        }
    }


  need_to_redraw();
}


void
CharacterSelector::
draw_character(const Character&  c, Widget*  wid, int  x_base, int  y_base)
{
  auto  src = c.data;

    for(int  yy = 0;  yy < 8;  ++yy)
    {
      auto  code = *src++;

        for(int  xx = 0;  xx < 8;  ++xx)
        {
          wid->draw_dot((code&0x80)? const_color::white:const_color::black,x_base+xx,y_base+yy);

          code <<= 1;
        }
    }
}


void
CharacterSelector::
render()
{
  auto  pt = content.point;

  fill();

    for(int  y = 0;  y < y_element_number;  ++y){
    for(int  x = 0;  x < x_element_number;  ++x){
      int  i = offset+((y<<3)|x);

        if(i >= Character::embedded_number)
        {
          goto NEXT;
        }


      auto&  c = Character::embedded_table[i];

      const int  x_base = pt.x+(element_width*x)+5;
      const int  y_base = pt.y+(element_width*y)+5;

        if(&c == now)
        {
          draw_rect(const_color::white,x_base-5,y_base-5,element_width-2,element_width-2);
        }


      draw_character(c,this,x_base,y_base);
    }}


NEXT:
  draw_rect(const_color::gray ,pt.x+cursor.x,pt.y+cursor.y,element_width,element_width);
}




}



