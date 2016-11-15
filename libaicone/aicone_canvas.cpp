#include"aicone_canvas.hpp"
#include"oat.hpp"




namespace oat{


Canvas::
Canvas():
l_callback(nullptr),
r_callback(nullptr),
type(PaintType::draw_dot),
color_index(1<<9),
eraser_flag(0),
grid_flag(0)
{
}


Canvas::
Canvas(IndexColorImageModule&&  m, int  pixel_size_, int  view_w, int  view_h):
IndexColorImage(std::move(m),pixel_size_,view_w,view_h),
l_callback(nullptr),
r_callback(nullptr),
type(PaintType::draw_dot),
color_index(1<<9),
eraser_flag(0),
grid_flag(0)
{
}




void
Canvas::
set_left_callback(Callback  cb)
{
  l_callback = cb;
}


void
Canvas::
set_right_callback(Callback  cb)
{
  r_callback = cb;
}


Point&
Canvas::
get_tool_point()
{
  return tool_point;
}


const Point&
Canvas::
get_const_tool_point() const
{
  return tool_point;
}


void
Canvas::
change_color_index(palette::index_t  i)
{
  color_index = i;
}


palette::index_t
Canvas::
get_color_index() const
{
  return eraser_flag? 0:color_index;
}


void
Canvas::
change_paint_type(PaintType  t)
{
    if(type != t)
    {
      type = t;

      provisional_dots.clear();

      first_point.x = -1;
    }
}


void
Canvas::
change_eraser_flag(bool  v)
{
  eraser_flag = v;
}


void
Canvas::
change_grid_flag(bool  v)
{
  grid_flag = v;

  need_to_redraw();
}




void
Canvas::
put_dot(const Dot&  dot, DotStack*  dots)
{
  auto&  dst = get_index(dot.x,dot.y);

    if(dst != dot.color_index)
    {
        if(dots)
        {
          dots->emplace_back(dot.x,dot.y,dst);
        }


      dst = dot.color_index;
    }
}


void
Canvas::
append(const DotStack&  dots)
{
    for(auto&  dot: dots)
    {
      get_index(dot.x,dot.y) = dot.color_index;
    }
}


void
Canvas::
settle_drawing()
{
  backup_dots.clear();

  first_point = -1;
}


void
Canvas::
cancel_drawing()
{
  append(backup_dots);

  backup_dots.clear();

  first_point = -1;

  need_to_redraw();
}


void
Canvas::
update_tool_point(const Mouse&  mouse)
{
  auto  pt = get_mouse_point(mouse);

/*
       if(pt.x <  (              border_width)){pt.x  =                            0;}
  else if(pt.x >= (content.width-border_width)){pt.x  = content.width-border_width*3;}
  else                                        {pt.x -=                border_width  ;}


       if(pt.y <  (               border_width)){pt.y  =                             0;}
  else if(pt.y >= (content.height-border_width)){pt.y  = content.height-border_width*3;}
  else                                         {pt.y -=                 border_width  ;}
*/

  pt.x /= pixel_size;
  pt.y /= pixel_size;

  pt.x += view_point.x;
  pt.y += view_point.y;

  tool_point = pt;
}


void
Canvas::
process_mouse(const Mouse&  mouse)
{
  master.change_dragging(mouse.left.test_pressing());

    if(mouse.test_moved())
    {
      update_tool_point(mouse);
 
      need_to_redraw();
    }


  draw(mouse);
}


void
Canvas::
process_when_mouse_left()
{
  cancel_drawing();
}


void
Canvas::
render()
{
  Image::render();

  auto  pt = content.point;

  Widget::draw_rect(const_color::white,pt.x+(pixel_size*tool_point.x),
                                       pt.y+(pixel_size*tool_point.y),pixel_size,pixel_size);

  const int  ww = pixel_size*view_width;

    if(grid_flag)
    {
        for(int  y = 0;  y < view_height;  ++y)
        {
          bool  flag = (y%4);

          int  xx = pt.x               ;
          int  yy = pt.y+(pixel_size*y);

          draw_hline(flag? const_color::light_gray:const_color::black,xx,yy  ,ww);
          draw_hline(flag? const_color::dark_gray :const_color::black,xx,yy+1,ww);
        }


        for(int  x = 0;  x < view_width ;  ++x)
        {  
          bool  flag = (x%4);

          int  xx = pt.x+(pixel_size*x);
          int  yy = pt.y               ;

          draw_vline(flag? const_color::light_gray:const_color::black,xx  ,yy,ww);
          draw_vline(flag? const_color::dark_gray :const_color::black,xx+1,yy,ww);
        }
    }
}


}




