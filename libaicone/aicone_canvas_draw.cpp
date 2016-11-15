#include"aicone_canvas.hpp"
#include"oat.hpp"
#include<cstdlib>




namespace oat{




void
Canvas::
draw_dot()
{
  auto&  dst = get_index(tool_point.x,tool_point.y);

    if(l_callback)
    {
      l_callback(*this);
    }


  dst = get_color_index();
}


void
Canvas::
draw_circle()
{
    if(first_point.x < 0)
    {
      settle_drawing();

      first_point = tool_point;

      return;
    }


  append(backup_dots);

  backup_dots.clear();


//http://members.chello.at/~easyfilter/bresenham.html
  int  x0 = first_point.x;
  int  y0 = first_point.y;
  int  x1 =  tool_point.x;
  int  y1 =  tool_point.y;

   int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
   long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
   long err = dx+dy+b1*a*a, e2; /* error of 1.step */

   if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
   if (y0 > y1) y0 = y1; /* .. exchange them */
   y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
   a *= 8*a; b1 = 8*b*b;


   const auto  i = get_color_index();

   do {
       put_dot(Dot(x1, y0,i),&backup_dots); /*   I. Quadrant */
       put_dot(Dot(x0, y0,i),&backup_dots); /*  II. Quadrant */
       put_dot(Dot(x0, y1,i),&backup_dots); /* III. Quadrant */
       put_dot(Dot(x1, y1,i),&backup_dots); /*  IV. Quadrant */
       e2 = 2*err;
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
   } while (x0 <= x1);
   
   while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
       put_dot(Dot(x0-1, y0,i),&backup_dots); /* -> finish tip of ellipse */
       put_dot(Dot(x1+1, y0++,i),&backup_dots); 
       put_dot(Dot(x0-1, y1,i),&backup_dots);
       put_dot(Dot(x1+1, y1--,i),&backup_dots); 
   }
}


void
Canvas::
draw_rect()
{
    if(first_point.x < 0)
    {
      settle_drawing();

      first_point = tool_point;

      return;
    }


  append(backup_dots);

  backup_dots.clear();


  const int  x = std::min(first_point.x,tool_point.x);
  const int  y = std::min(first_point.y,tool_point.y);

  const int  w = std::abs(first_point.x-tool_point.x)+1;
  const int  h = std::abs(first_point.y-tool_point.y)+1;

  const int  i = get_color_index();

    for(int  xx = 0;  xx < w;  ++xx)
    {
      put_dot(Dot(x+xx,y    ,i),&backup_dots);
      put_dot(Dot(x+xx,y+h-1,i),&backup_dots);
    }


    for(int  yy = 0;  yy < h;  ++yy)
    {
      put_dot(Dot(x    ,y+yy,i),&backup_dots);
      put_dot(Dot(x+w-1,y+yy,i),&backup_dots);
    }
}


void
Canvas::
draw_filled_rect()
{
    if(first_point.x < 0)
    {
      settle_drawing();

      first_point = tool_point;

      return;
    }


  append(backup_dots);

  backup_dots.clear();


  const int  x = std::min(first_point.x,tool_point.x);
  const int  y = std::min(first_point.y,tool_point.y);

  const int  w = std::abs(first_point.x-tool_point.x)+1;
  const int  h = std::abs(first_point.y-tool_point.y)+1;

  const int  i = get_color_index();

    for(int  yy = 0;  yy < h;  ++yy)
    {
        for(int  xx = 0;  xx < w;  ++xx)
        {
          put_dot(Dot(x+xx,y+yy,i),&backup_dots);
        }
    }
}


void
Canvas::
draw(const Mouse&  mouse)
{
    switch(type)
    {
      case(PaintType::draw_dot):
          if(mouse.left.test_pressing())
          {
            draw_dot();

            need_to_redraw();
          }

        else
          if(mouse.left.test_unpressed())
          {
          }
        break;
      case(PaintType::draw_line):
          if(mouse.left.test_pressing())
          {
            draw_line();

            need_to_redraw();
          }

        else
          if(mouse.left.test_unpressed())
          {
              if(l_callback)
              {
                l_callback(*this);
              }


            settle_drawing();
          }
        break;
      case(PaintType::draw_circle):
          if(mouse.left.test_pressing())
          {
            draw_circle();

            need_to_redraw();
          }

        else
          if(mouse.left.test_unpressed())
          {
              if(l_callback)
              {
                l_callback(*this);
              }


            settle_drawing();
          }
        break;
      case(PaintType::draw_rect):
          if(mouse.left.test_pressing())
          {
            draw_rect();

            need_to_redraw();
          }

        else
          if(mouse.left.test_unpressed())
          {
              if(l_callback)
              {
                l_callback(*this);
              }


            settle_drawing();
          }
        break;
      case(PaintType::fill_rect):
          if(mouse.left.test_pressing())
          {
            draw_filled_rect();

            need_to_redraw();
          }

        else
          if(mouse.left.test_unpressed())
          {
              if(l_callback)
              {
                l_callback(*this);
              }


            settle_drawing();
          }
        break;
      case(PaintType::fill_area):
          if(mouse.left.test_unpressed())
          {
            fill_area();

              if(l_callback)
              {
                l_callback(*this);
              }


            need_to_redraw();
          }
        break;
    }
}




}




