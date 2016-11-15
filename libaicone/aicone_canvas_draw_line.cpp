#include"aicone_canvas.hpp"
#include"oat.hpp"
#include<cstdlib>




namespace oat{




void
Canvas::
draw_line()
{
    if(first_point.x < 0)
    {
      settle_drawing();

      first_point = tool_point;

      return;
    }


  constexpr int  shift_amount = 16;

  int  x0 = first_point.x;
  int  y0 = first_point.y;
  int  x1 =  tool_point.x;
  int  y1 =  tool_point.y;

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


  append(backup_dots);

  backup_dots.clear();

  x0 <<= x_shift_amount;
  y0 <<= y_shift_amount;

    for(;;)
    {
      put_dot(Dot((x0>>x_shift_amount),
                  (y0>>y_shift_amount),eraser_flag? 0:color_index),&backup_dots);

        if(!step_count--)
        {
          break;
        }


      x0 += x_add_amount;
      y0 += y_add_amount;
    }
}


}




