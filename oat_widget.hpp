#ifndef OAT_WIDGET_HPP
#define OAT_WIDGET_HPP


#include<vector>
#include<list>
#include<string>
#include"oat_color.hpp"
#include"oat_point.hpp"
#include"oat_box.hpp"
#include"oat_mouse.hpp"
#include"oat_keyboard.hpp"




#ifndef report
#define report  printf("[report in %s] %s %d\n",__FILE__,__func__,__LINE__)
#define printd(d)  printf("[printd %s] %d\n",#d,d)
#endif


namespace oat{




class
Widget: public Box
{
protected:
  uint32_t  flags;

  Widget*  parent;

  void*  userdata;

  int  child_count;

  using WidgetList = std::list<Widget*>;

  WidgetList  children;

  void  try_redraw();

  void  reform();
  void  redraw();
  void  redraw_perfect();

public:
  enum class Flag{
    hidden                    =  1,
    needed_to_reform          =  2,
    needed_to_redraw_self     =  4,
    needed_to_redraw_child    =  8,
    needed_to_redraw_perfect  = 16,
    size_is_changed           = 32,
  };


           Widget();
  virtual ~Widget();


  Widget*  get_parent() const;

  void   set_userdata(void*  ptr)      ;
  void*  get_userdata(          ) const;

  Point  get_mouse_point(const Mouse&  mouse) const;

  void  change_content_width( int  w);
  void  change_content_height(int  h);

  bool   test_flag(Flag  f) const;
  void    set_flag(Flag  f);
  void  unset_flag(Flag  f);
  void  notify_flag(Flag  f);

  Widget*&  join(Widget*  child, int  x, int  y);
  void    rejoin(Widget&  child, int  x, int  y);

  const Box&  get_box() const;

  Widget*  scan(const Point&  pt);

  void  need_to_reform();
  void  need_to_redraw();

  void  update_sizes() override;

  virtual void  process_mouse(const Mouse&  mouse){};

  virtual void  process_when_mouse_entered(){};
  virtual void  process_when_mouse_left(){};

  template<typename  T>
  void  process_children(T&  t)
  {
    int  i = 0;

      for(auto  child: children)
      {
          if(child)
          {
            t(*child,i);
          }


        ++i;
      }
  }

  void  ascend_process_mouse(const Mouse&  mouse);

  virtual void  render();
  


//functions for render
  void  fill(                  );
  void  fill(const Color& color);

  void  draw_dot(       const Color& color, int  x, int  y);
  void  draw_dot_safely(const Color& color, int  x, int  y);

  void  draw_unicode(const Color& color, char16_t  c, int  x, int  y);

  void  draw_text(const Color& color, const std::string&      u8s, int  x, int  y);
  void  draw_text(const Color& color, const std::u16string&  u16s, int  x, int  y);

  void  draw_line(const Color& color, int  x0, int  y0, int  x1, int  y1);

  void  draw_vline(const Color& color, int  x, int  y, int  w, bool  brok=false);
  void  draw_hline(const Color& color, int  x, int  y, int  w, bool  brok=false);

  void  draw_vline_safely(const Color& color, int  x, int  y, int  w, bool  brok=false);
  void  draw_hline_safely(const Color& color, int  x, int  y, int  w, bool  brok=false);

  void  draw_rect(const Color& color, int  x, int  y, int  w, int  h, bool  brok=false);
  void  fill_rect(const Color& color, int  x, int  y, int  w, int  h);

  void  draw_rect_safely(const Color& color, int  x, int  y, int  w, int  h, bool  brok=false);

  void   draw_convex_rect(const Color& color, int  x, int  y, int  w, int  h);
  void  draw_concave_rect(const Color& color, int  x, int  y, int  w, int  h);

  void  draw_input_form(int  x, int  y, int  w, int  h);

  void  draw_frame(const Color& color, int  width, int  x, int  y, int  w, int  h);

};


template<typename  T>
Widget*
as_widget(T&  t)
{
  return static_cast<Widget*>(t);
}


}


#endif




