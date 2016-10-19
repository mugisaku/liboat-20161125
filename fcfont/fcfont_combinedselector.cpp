#include"fcfont_combinedselector.hpp"
#include"fcfont_characterselector.hpp"


using namespace oat;


namespace fcfont{


CombinedSelector::
CombinedSelector(Callback  cb):
callback(cb),
now(Combined::embedded_table),
buffer(u"? U+XXXX"),
offset(0)
{
  style.background_color = const_color::black;

  change_content_width( element_width *x_element_number);
  change_content_height(element_height*y_element_number);
}




Combined*
CombinedSelector::
get() const
{
  return now;
}


const char16_t*
CombinedSelector::
get_buffer() const
{
  return buffer;
}


void
CombinedSelector::
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
CombinedSelector::
down()
{
  offset += x_element_number*y_element_number;

  need_to_redraw();
}


void
CombinedSelector::
process_mouse(const Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x = cursor.x/element_width *element_width ;
  cursor.y = cursor.y/element_height*element_height;

    if(mouse.left.test_pressing())
    {
      int  x = cursor.x/element_width;
      int  y = cursor.y/element_height;

      unsigned int  i = offset+((y<<3)|x);

        if(i < Combined::embedded_number)
        {
          now = &Combined::embedded_table[i];

          buffer[0] = now->unicode;

          static const char16_t  c_table[] = u"0123456789ABCDEF";

          auto  p = &buffer[4];

          *p++ = c_table[(now->unicode>>12)&0xF];
          *p++ = c_table[(now->unicode>> 8)&0xF];
          *p++ = c_table[(now->unicode>> 4)&0xF];
          *p   = c_table[(now->unicode>> 0)&0xF];

            if(callback)
            {
              callback(get_userdata());
            }
        }
    }


  need_to_redraw();
}


void
CombinedSelector::
draw_combined(const Combined&  cmb, Widget*  wid, int  x, int  y)
{
  auto  upper = Character::pointer_table[cmb.upper];
  auto  lower = Character::pointer_table[cmb.lower];


    if(upper){CharacterSelector::draw_character(*upper,wid,x,y                );}
    if(lower){CharacterSelector::draw_character(*lower,wid,x,y+Character::size);}
}


void
CombinedSelector::
render()
{
  auto  pt = content.point;

  fill();

    for(int  y = 0;  y < y_element_number;  ++y){
    for(int  x = 0;  x < x_element_number;  ++x){
      int  i = offset+((y<<3)|x);

        if(i >= Combined::embedded_number)
        {
          goto NEXT;
        }


      auto&  c = Combined::embedded_table[i];

      const int  x_base = pt.x+(element_width *x)+5;
      const int  y_base = pt.y+(element_height*y)+5;

        if(&c == now)
        {
          draw_rect(const_color::white,x_base-5,y_base-5,element_width-2,element_height-2);
        }


      draw_combined(c,this,x_base,y_base);
    }}


NEXT:
  draw_rect(const_color::gray ,pt.x+cursor.x,pt.y+cursor.y,element_width,element_height);
}




}



