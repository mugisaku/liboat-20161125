#include"oat_container.hpp"




namespace oat{




Container::
~Container()
{
    for(auto  ptr: children)
    {
      delete ptr;
    }
}




void
Container::
join(Widget*  child, int  x, int  y)
{
    if(child)
    {
      child->change_parent(*this,x,y);

      children.emplace_back(child);
    }
}




Widget*
Container::
scan(const Point&  pt)
{
    if(content.test(pt))
    {
        for(auto  child: children)
        {
            if(child && !child->test_flag(hidden_flag))
            {
              auto  res = child->scan(pt);

                if(res)
                {
                  return res;
                }
            }
        }


      return this;
    }


  return nullptr;
}




void
Container::
update_sizes()
{
  int  w = 0;
  int  h = 0;

    for(auto  child: children)
    {
        if(child && !child->test_flag(hidden_flag))
        {
          child->update_sizes();

          auto&  rpt = child->get_relative_point();

          w = std::max(w,(rpt.x+child->width ));
          h = std::max(h,(rpt.y+child->height));
        }
    }


  change_content_width( w);
  change_content_height(h);

  Box::update_sizes();
}


void
Container::
reform()
{
  const int  old_right  = get_right() ;
  const int  old_bottom = get_bottom();

  update_points(parent? &parent->content.point:nullptr);

    for(auto  child: children)
    {
        if(child && !child->test_flag(hidden_flag) && child->test_flag(needed_to_reform_flag))
        {
          child->reform();

          set_flag(needed_to_redraw_child_flag);
        }
    }


  update_sizes();

    if((get_right()  > old_right ) ||
       (get_bottom() > old_bottom))
    {
      set_flag(needed_to_redraw_perfect_flag);
    }

  else
    {
      set_flag(needed_to_redraw_self_flag);
    }


  notify_flag(needed_to_redraw_child_flag);

  unset_flag(needed_to_reform_flag);
}


void
Container::
redraw()
{
  render();

    if(test_flag(needed_to_redraw_child_flag))
    {
        for(auto  child: children)
        {
            if(child)
            {
              child->try_redraw();
            }
        }


      unset_flag(needed_to_redraw_child_flag);
    }


  unset_flag(needed_to_redraw_self_flag);
}


void
Container::
redraw_perfect()
{
  fill();

  render();

    for(auto  child: children)
    {
        if(child && !child->test_flag(hidden_flag))
        {
          child->redraw_perfect();
        }
    }


  unset_flag(needed_to_redraw_child_flag);
  unset_flag(needed_to_redraw_self_flag);
  unset_flag(needed_to_redraw_perfect_flag);
}




void
Container::
process_mouse(const Mouse&  mouse)
{
}


void
Container::
process_when_mouse_entered()
{
}


void
Container::
process_when_mouse_left()
{
}




void
Container::
render()
{
    for(auto  child: children)
    {
      child->render();
    }
}


}




