#include"oat_master.hpp"
#include"oat_buttonmodule.hpp"
#include"oat.hpp"




namespace{


bool
dragging_flag;


}


namespace oat{




Master::
Master():
current(nullptr)
{
}




void
Master::
change_dragging(bool  v)
{
  dragging_flag = v;
}


void
Master::
process(Mouse&  mouse)
{
    if(current)
    {
        if(dragging_flag)
        {
          current->get_content_rectangle().grab(mouse.point);

          current->process_mouse(mouse);

          current->ascend_process_mouse(mouse);

          return;
        }

      else
        {
          auto  res = current->scan(mouse.point);

            if(res == current)
            {
              current->process_mouse(mouse);

              current->ascend_process_mouse(mouse);

              return;
            }

          else
            {
              current->process_when_mouse_left();

              current = nullptr;
            }
        }
    }


    if(!current)
    {
      current = scan(mouse.point);

        if(current)
        {
          current->process_when_mouse_entered();

          current->process_mouse(mouse);

          current->ascend_process_mouse(mouse);
        }
    }
}


bool
Master::
update()
{
  ButtonModule::unset_shortlived_all();

    if(test_flag(needed_to_reform_flag))
    {
      reform();

        if((module.get_width()  < width ) ||
           (module.get_height() < height))
        {
          module.resize(width,height);
        }
    }


  bool  flag = (test_flag(needed_to_redraw_perfect_flag) ||
                test_flag(needed_to_redraw_self_flag   ) ||
                test_flag(needed_to_redraw_child_flag  ));

  try_redraw();

  return flag;
}


Color&
Master::
get_pixel(int  x, int  y) const
{
  return module.get_element(x,y);
}


const DirectColorImageModule&
Master::
get_module() const
{
  return module;
}


}




