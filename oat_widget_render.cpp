#include"oat.hpp"
#include"oat_font.hpp"
#include<cstdlib>




namespace oat{




void
Widget::
fill()
{
  int  x = padding.point.x;
  int  y = padding.point.y;
  int  w = padding.width;
  int  h = padding.height;

  fill_rect(style.background_color,x,y,w,h);


  x = border.point.x;
  y = border.point.y;
  w = border.width ;
  h = border.height;

    for(int  n = style.border_width;  n;  --n)
    {
      draw_rect(style.border_color,x,y,w,h);

      ++x;
      ++y;
      w -= 2;
      h -= 2;
    }
}


void
Widget::
fill(const Color&  color)
{
  fill_rect(color,0,0,width,height);
}


void
Widget::
draw_dot(const Color& color, int  x, int  y)
{
  master.get_pixel(x,y) = color;
}


void
Widget::
draw_dot_safely(const Color& color, int  x, int  y)
{
    if((x >=      0) &&
       (x <   width) &&
       (y >=      0) &&
       (y <  height))
    {
      master.get_pixel(x,y) = color;
    }
}


void
Widget::
draw_unicode(const Color& color, char16_t  c, int  x, int  y)
{
  auto  p = font::get_data(c);

    if(p)
    {
      x += font::left_padding;
      y += font::top_padding;

        for(int  yy = 0;  yy < font::size;  ++yy)
        {
          uint32_t  code = *p++;

            for(int  xx = 0;  xx < font::size;  ++xx)
            {
                if(code&0x8000)
                {
                  draw_dot(color,x+xx,y+yy);
                }


              code <<= 1;
            }
        }
    }
}


void
Widget::
draw_text(const Color& color, const std::string&  u8s, int  x, int  y)
{
    for(auto  c: u8s)
    {
      draw_unicode(color,c,x,y);

      x += font::width;
    }
}


void
Widget::
draw_text(const Color& color, const std::u16string&  u16s, int  x, int  y)
{
    for(auto  c: u16s)
    {
      draw_unicode(color,c,x,y);

      x += font::width;
    }
}


void
Widget::
draw_line(const Color& color, int  x0, int  y0, int  x1, int  y1)
{
  constexpr int  shift_amount = 16;

  int  x_dist = std::abs(x0-x1);
  int  y_dist = std::abs(y0-y1);

  int  x_add_amount;
  int  y_add_amount;

  int  x_shift_amount;
  int  y_shift_amount;

  int  step_count;

    if(x_dist >= y_dist)
    {
      step_count = x_dist;

      x_add_amount   = (x0 < x1)? 1:-1;
      y_add_amount   = x_dist? (y_dist<<shift_amount)/x_dist:0;
      x_shift_amount = 0;
      y_shift_amount = shift_amount;

        if(y0 > y1)
        {
          y_add_amount = -y_add_amount;
        }
    }

  else
    {
      step_count = y_dist;

      x_add_amount   = y_dist? (x_dist<<shift_amount)/y_dist:0;
      y_add_amount   = (y0 < y1)? 1:-1;
      x_shift_amount = shift_amount;
      y_shift_amount = 0;

        if(x0 > x1)
        {
          x_add_amount = -x_add_amount;
        }
    }


  x0 <<= x_shift_amount;
  y0 <<= y_shift_amount;

    for(;;)
    {
      draw_dot(color,(x0>>x_shift_amount),
                     (y0>>y_shift_amount));

        if(!step_count--)
        {
          break;
        }


      x0 += x_add_amount;
      y0 += y_add_amount;
    }
}


void
Widget::
draw_vline(const Color& color, int  x, int  y, int  w, bool  brok)
{
    if(!brok)
    {
        while(w--)
        {
          draw_dot(color,x,y++);
        }
    }

  else
    {
      w /= 2;

        while(w--)
        {
          draw_dot(color,x,y);

          y += 2;
        }
    }
}


void
Widget::
draw_hline(const Color& color, int  x, int  y, int  w, bool  brok)
{
    if(!brok)
    {
        while(w--)
        {
          draw_dot(color,x++,y);
        }
    }

  else
    {
      w /= 2;

        while(w--)
        {
          draw_dot(color,x,y);

          x += 2;
        }
    }
}




void
Widget::
draw_vline_safely(const Color& color, int  x, int  y, int  w, bool  brok)
{
    if((x >=    0) &&
       (x < width))
    {
        if(y < 0)
        {
            if(w < -y)
            {
              return;
            }


          w += y    ;
               y = 0;
        }


        if((y+w) >= height)
        {
          w = (height-y);
        }


      draw_vline(color,x,y,w,brok);
    }
}


void
Widget::
draw_hline_safely(const Color& color, int  x, int  y, int  w, bool  brok)
{
    if((y >=      0) &&
       (y <  height))
    {
        if(x < 0)
        {
            if(w < -x)
            {
              return;
            }


          w += x    ;
               x = 0;
        }


        if((x+w) >= width)
        {
          w = (width-x);
        }


      draw_hline(color,x,y,w,brok);
    }
}




void
Widget::
draw_rect(const Color& color, int  x, int  y, int  w, int  h, bool  brok)
{
  draw_vline(color,x    ,y,h,brok);
  draw_vline(color,x+w-1,y,h,brok);

  draw_hline(color,x,y    ,w,brok);
  draw_hline(color,x,y+h-1,w,brok);
}


void
Widget::
fill_rect(const Color& color, int  x, int  y, int  w, int  h)
{
    for(int  yy = 0;  yy < h;  ++yy){
    for(int  xx = 0;  xx < w;  ++xx){
      draw_dot(color,x+xx,y+yy);
    }}
}




void
Widget::
draw_rect_safely(const Color& color, int  x, int  y, int  w, int  h, bool  brok)
{
  draw_vline_safely(color,x    ,y,h,brok);
  draw_vline_safely(color,x+w-1,y,h,brok);

  draw_hline_safely(color,x,y    ,w,brok);
  draw_hline_safely(color,x,y+h-1,w,brok);
}




void
Widget::
draw_convex_rect(const Color& color, int  x, int  y, int  w, int  h)
{
  fill_rect(color,x,y,w,h);

  draw_rect(const_color::white,x,y  ,w,  2);
  draw_rect(const_color::white,x,y+2,2,h-2);

  draw_rect(const_color::dark_gray,x    ,y+h-2,w,  2);
  draw_rect(const_color::dark_gray,x+w-2,y+2  ,2,h-2);
}


void
Widget::
draw_concave_rect(const Color& color, int  x, int  y, int  w, int  h)
{
  fill_rect(color,x,y,w,h);

  draw_rect(const_color::dark_gray,x  ,y  ,w  ,h  );
  draw_rect(const_color::dark_gray,x+1,y+1,w-2,h-2);

  draw_vline(const_color::white,x+w-1,y+  1,h-2);
  draw_hline(const_color::white,x+  1,y+h-1,w-2);
}
 

void
Widget::
draw_input_form(int  x, int  y, int  w, int  h)
{
  fill_rect(const_color::white,x+1,y+1,w-2,h-2);

  draw_hline(const_color::black,x    ,y    ,w);
  draw_vline(const_color::black,x    ,y    ,h);
  draw_hline(const_color::white,x    ,y+h-1,w);
  draw_vline(const_color::white,x+w-1,y    ,h);
}


void
Widget::
draw_frame(const Color& color, int  width, int  x, int  y, int  w, int  h)
{
}


}




