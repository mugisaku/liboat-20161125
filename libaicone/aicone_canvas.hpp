#ifndef AICONE_CANVAS_HPP
#define AICONE_CANVAS_HPP


#include"oat_widget.hpp"
#include"oat_arraymodule.hpp"
#include"oat_image.hpp"


namespace oat{


class
Canvas: public IndexColorImage
{
public:
  using Callback = void  (*)(Canvas&  cv);

  enum class PaintType{
    draw_dot,
    draw_line,
    draw_circle,
    draw_rect,
    fill_rect,
    fill_area,
  };

private:
  struct Dot: public Point{
    palette::index_t  color_index;

    constexpr Dot(int  x, int  y, palette::index_t  i):
    Point(x,y), color_index(i){}
  };


  using DotStack = std::vector<Dot>;

  DotStack  provisional_dots;
  DotStack       backup_dots;

  Callback  l_callback;
  Callback  r_callback;

  Point  tool_point;

  Point  first_point;

  palette::index_t  color_index;

  bool  eraser_flag;
  bool    grid_flag;

  PaintType  type;


  void  append(const DotStack&  dots);

  void  settle_drawing();
  void  cancel_drawing();

  void  put_dot(const Dot&  dot, DotStack*  dots=nullptr);

  void  draw_dot();
  void  draw_line();
  void  draw_circle();
  void  draw_rect();
  void  draw_filled_rect();
  void  fill_area();
  void  draw(const Mouse&  mouse);

public:
  Canvas();
  Canvas(IndexColorImageModule&&  m, int  pixel_size_=1, int  view_w=0, int  view_h=0);


        Point&  get_tool_point()            ;
  const Point&  get_const_tool_point() const;

  void  change_color_index(palette::index_t  i);
  palette::index_t  get_color_index() const;

  void  change_paint_type(PaintType  t);

  void  set_left_callback(Callback  cb);
  void  set_right_callback(Callback  cb);

  void  change_eraser_flag(bool  v);
  void    change_grid_flag(bool  v);

  void  update_tool_point(const Mouse&  mouse);


  void  reverse_horizontally();
  void  reverse_vertically();
  void  revolve();



  void  process_mouse(const Mouse&  mouse) override;
  void  process_when_mouse_left() override;

  void  render() override;

};


}




#endif




