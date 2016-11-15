#ifndef OAT_BOX_HPP
#define OAT_BOX_HPP


#include"oat_point.hpp"
#include"oat_color.hpp"




namespace oat{




struct
Style
{
  Length    left_padding=0;
  Length   right_padding=0;
  Length     top_padding=0;
  Length  bottom_padding=0;

  Length    left_margin=0;
  Length   right_margin=0;
  Length     top_margin=0;
  Length  bottom_margin=0;

  Length  border_width=0;

  Color  background_color;
  Color        font_color;
  Color      border_color;

};


class
Box: public Rectangle
{
protected:
  const char*  name;

  Point  relative_point;

  Rectangle   border;
  Rectangle  padding;
  Rectangle  content;

public:
  Style  style;

  Box();


  const Rectangle&  get_content_rectangle() const;

  const Point&  get_relative_point() const;

  void  change_name(const char*  s);

  void  update_points(const Point*  base_point=nullptr);

  virtual void  update_sizes();

  void  print() const;

};


}


#endif




