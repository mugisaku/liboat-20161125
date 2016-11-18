#include"oat_widget.hpp"
#include"oat_container.hpp"
#include"oat.hpp"




namespace oat{




Widget::
Widget():
parent(nullptr),
userdata(nullptr),
flags(0)
{
}


Widget::
~Widget()
{
}




void
Widget::
change_parent(Container&  new_parent, int  x, int  y)
{
    if(parent)
    {
      printf("すでに親ウィジェットが設定されています\n");

      throw;
    }


  parent = &new_parent;

  relative_point.reset(x,y);

  need_to_reform();
}


Container*
Widget::
get_parent() const
{
  return parent;
}


void   Widget::set_userdata(void*  ptr)      {       userdata = ptr;}
void*  Widget::get_userdata(          ) const{return userdata      ;}




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




bool   Widget::test_flag(int  f) const{return(flags&f);}
void    Widget::set_flag(int  f){flags |=  f;}
void  Widget::unset_flag(int  f){flags &= ~f;}


void
Widget::
notify_flag(int  f)
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
     set_flag(needed_to_reform_flag);
  notify_flag(needed_to_reform_flag);
}


void
Widget::
need_to_redraw()
{
     set_flag(needed_to_redraw_self_flag );
  notify_flag(needed_to_redraw_child_flag);
}


void
Widget::
change_content_width(int  w)
{
    if(content.width != w)
    {
      content.width = w;

      set_flag(size_is_changed_flag);

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

      set_flag(size_is_changed_flag);

      need_to_reform();
    }
}


Widget*
Widget::
scan(const Point&  pt)
{
    if(content.test(pt))
    {
      return this;
    }


  return nullptr;
}




void
Widget::
redraw()
{
  render();
}


void
Widget::
redraw_perfect()
{
  fill();

  render();
}


void
Widget::
reform()
{
  const int  old_right  = get_right() ;
  const int  old_bottom = get_bottom();

  update_points(parent? &parent->content.point:nullptr);


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
Widget::
try_redraw()
{
    if(!test_flag(hidden_flag))
    {
        if(test_flag(needed_to_redraw_perfect_flag))
        {
          redraw_perfect();
        }

      else
        if(test_flag(needed_to_redraw_self_flag) ||
           test_flag(needed_to_redraw_child_flag))
        {
          redraw();
        }
    }
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




