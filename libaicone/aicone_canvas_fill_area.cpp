#include"aicone_canvas.hpp"
#include"oat.hpp"
#include<stack>




namespace oat{


namespace{
ArrayModule<uint8_t>
field;


struct
Frame
{
  int  x;
  int  y;

  int  phase;

  Frame(int  x_, int  y_, int  p=0):
  x(x_), y(y_), phase(p){}

};


}


void
Canvas::
fill_area()
{
  const palette::index_t  target_i = get_index(tool_point.x,tool_point.y);

  const palette::index_t  source_i = get_color_index();

    if(target_i == source_i)
    {
      return;
    }


  field.resize(module.get_width(),module.get_height());

  field.fill(0);

  std::stack<Frame>  stack;

  stack.emplace(tool_point.x,tool_point.y);

START:
    if(stack.empty())
    {
      return;
    }


  auto&  top = stack.top();

    switch(top.phase)
    {
      case(0):
        {
          auto&  mark = field.get_element(top.x,top.y);

            if(mark)
            {
              stack.pop();

              goto START;
            }


          mark = 1;

          auto&  dst = get_index(top.x,top.y);

            if(dst == target_i)
            {
              put_dot(Dot(top.x,top.y,source_i));
            }

          else
            {
              stack.pop();

              goto START;
            }
        }
      case(1):
          if(top.x)
          {
            top.phase = 2;

            stack.emplace(top.x-1,top.y);

            goto START;
          }
      case(2):
          if(top.y)
          {
            top.phase = 3;

            stack.emplace(top.x,top.y-1);

            goto START;
          }
      case(3):
          if(top.x < (module.get_width()-1))
          {
            top.phase = 4;

            stack.emplace(top.x+1,top.y);

            goto START;
          }
      case(4):
          if(top.y < (module.get_height()-1))
          {
            top.phase = 5;

            stack.emplace(top.x,top.y+1);

            goto START;
          }
      case(5):
      default:;
    }


  stack.pop();

  goto START;
}


}




