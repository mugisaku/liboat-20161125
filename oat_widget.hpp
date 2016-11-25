#ifndef OAT_WIDGET_HPP
#define OAT_WIDGET_HPP


#include<vector>
#include<list>
#include<string>
#include"oat_color.hpp"
#include"oat_point.hpp"
#include"oat_box.hpp"
#include"oat_mouse.hpp"




#ifndef report
#define report  printf("[report in %s] %s %d\n",__FILE__,__func__,__LINE__)
#define printd(d)  printf("[printd %s] %d\n",#d,d)
#endif


namespace oat{


struct Container;


class
Widget: public Box
{
protected:
  uint32_t  flags;

  Container*  parent;

  void*  userdata;

public:
  static constexpr int  hidden_flag                    =  1;
  static constexpr int  needed_to_reform_flag          =  2;
  static constexpr int  needed_to_redraw_self_flag     =  4;
  static constexpr int  needed_to_redraw_child_flag    =  8;
  static constexpr int  needed_to_redraw_perfect_flag  = 16;
  static constexpr int  size_is_changed_flag           = 32;


           Widget();
  virtual ~Widget();


  void  change_parent(Container&  new_parent, int  x, int  y);

  Container*  get_parent() const;

  void   set_userdata(void*  ptr)      ;
  void*  get_userdata(          ) const;

  Point  get_mouse_point(const Mouse&  mouse) const;

  void  change_content_width( int  w);
  void  change_content_height(int  h);

  bool   test_flag(int  f) const;
  void    set_flag(int  f);
  void  unset_flag(int  f);
  void  notify_flag(int  f);

  const Box&  get_box() const;

  void  need_to_reform();
  void  need_to_redraw();

  void  try_redraw();

  virtual Widget*  scan(const Point&  pt);

  virtual void  reform();
  virtual void  redraw();
  virtual void  redraw_perfect();

  virtual void  process_mouse(const Mouse&  mouse){};

  virtual void  process_when_mouse_entered(){};
  virtual void  process_when_mouse_left(){};

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


class
WidgetUpdater
{
  std::vector<Widget*>  target_list;

public:
  WidgetUpdater(std::initializer_list<Widget*>  ls={}):
  target_list(ls){}

  void  operator()() const
  {
      for(auto  target: target_list)
      {
        target->need_to_redraw();
      }
  }

};


}


#endif




