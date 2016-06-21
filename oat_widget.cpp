#include"oat_widget.hpp"
#include"oat.hpp"




namespace oat{




Widget::
Widget():
parent(nullptr),
userdata(nullptr),
flags(0),
child_count(0)
{
}


Widget::
~Widget()
{
    for(auto  ptr: children)
    {
      delete ptr;
    }
}




Widget*
Widget::
get_parent() const
{
  return parent;
}


void   Widget::set_userdata(void*  ptr)      {       userdata = ptr;}
void*  Widget::get_userdata(          ) const{return userdata      ;}


Widget*&
Widget::
join(Widget*  child, int  x, int  y)
{
    if(child)
    {
      child->parent = this;

      child->relative_point.reset(x,y);

      child->need_to_reform();
    }


  children.emplace_back(child);

  child_count += 1;

  return children.back();
}


void
Widget::
rejoin(Widget&  child, int  x, int  y)
{
  child.parent = this;

  child.relative_point.reset(x,y);

  child.need_to_reform();
}




const Box&
Widget::
get_box() const
{
  return *this;
}


Point
Widget::
get_mouse_point(const Mouse&  mouse) const
{
  return mouse.point-content.point;
}


Widget*
Widget::
scan(const Point&  pt)
{
    if(content.test(pt))
    {
        for(auto  child: children)
        {
            if(child && !child->test_flag(Flag::hidden))
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




bool   Widget::test_flag(Flag  f) const{return(flags&static_cast<int>(f));}
void    Widget::set_flag(Flag  f){flags |=  static_cast<int>(f);}
void  Widget::unset_flag(Flag  f){flags &= ~static_cast<int>(f);}

void
Widget::
notify_flag(Flag  f)
{
    if(parent && !parent->test_flag(f))
    {
      parent->set_flag(f);

      parent->notify_flag(f);
    }
}


void
Widget::
need_to_reform()
{
     set_flag(Flag::needed_to_reform);
  notify_flag(Flag::needed_to_reform);
}


void
Widget::
need_to_redraw()
{
     set_flag(Flag::needed_to_redraw_self );
  notify_flag(Flag::needed_to_redraw_child);
}


void
Widget::
change_content_width(int  w)
{
    if(content.width != w)
    {
      content.width = w;

      set_flag(Flag::size_is_changed);

      need_to_reform();
    }
}


void
Widget::
change_content_height(int  h)
{
    if(content.height != h)
    {
      content.height = h;

      set_flag(Flag::size_is_changed);

      need_to_reform();
    }
}


void
Widget::
update_sizes()
{
  int  w = 0;
  int  h = 0;

    for(auto  child: children)
    {
        if(child && !child->test_flag(Flag::hidden))
        {
          child->update_sizes();

            if(child_count)
            {
              w = std::max(w,(child->relative_point.x+child->width ));
              h = std::max(h,(child->relative_point.y+child->height));
            }
        }
    }


    if(child_count)
    {
      change_content_width( w);
      change_content_height(h);
    }


  Box::update_sizes();
}


void
Widget::
reform()
{
  const int  old_right  = get_right() ;
  const int  old_bottom = get_bottom();

  update_points(parent? &parent->content.point:nullptr);

    for(auto  child: children)
    {
        if(child && !child->test_flag(Flag::hidden) && child->test_flag(Flag::needed_to_reform))
        {
          child->reform();

          set_flag(Flag::needed_to_redraw_child);
        }
    }


  update_sizes();

    if((get_right()  > old_right ) ||
       (get_bottom() > old_bottom))
    {
      set_flag(Flag::needed_to_redraw_perfect);
    }

  else
    {
      set_flag(Flag::needed_to_redraw_self);
    }


  notify_flag(Flag::needed_to_redraw_child);

  unset_flag(Flag::needed_to_reform);
}


void
Widget::
try_redraw()
{
    if(!test_flag(Flag::hidden))
    {
        if(test_flag(Flag::needed_to_redraw_perfect))
        {
          redraw_perfect();
        }

      else
        if(test_flag(Flag::needed_to_redraw_self) ||
           test_flag(Flag::needed_to_redraw_child))
        {
          redraw();
        }
    }
}


void
Widget::
redraw()
{
  render();

    if(test_flag(Flag::needed_to_redraw_child))
    {
        for(auto  child: children)
        {
            if(child)
            {
              child->try_redraw();
            }
        }


      unset_flag(Flag::needed_to_redraw_child);
    }


  unset_flag(Flag::needed_to_redraw_self);
}


void
Widget::
redraw_perfect()
{
  fill();

  render();

    for(auto  child: children)
    {
        if(child && !child->test_flag(Flag::hidden))
        {
          child->redraw_perfect();
        }
    }


  unset_flag(Flag::needed_to_redraw_child);
  unset_flag(Flag::needed_to_redraw_self);
  unset_flag(Flag::needed_to_redraw_perfect);
}




void
Widget::
ascend_process_mouse(const Mouse&  mouse)
{
  auto  p = parent;

    while(p)
    {
      p->process_mouse(mouse);

      p = p->get_parent();
    }
}


void
Widget::
render()
{
}


}




