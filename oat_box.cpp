#include"oat_box.hpp"
#include"oat.hpp"
#include<cstdio>




namespace oat{




Box::
Box():
name(""),
style(default_style)
{
}




const Rectangle&
Box::
get_content_rectangle() const
{
  return content;
}


const Point&
Box::
get_relative_point() const
{
  return relative_point;
}


void
Box::
change_name(const char*  s)
{
  name = s;
}


void
Box::
update_points(const Point*  base_point)
{
  point = relative_point;

    if(base_point)
    {
      point += *base_point;
    }


  border.point.x = point.x+style.left_margin;
  border.point.y = point.y+style.top_margin ;

  padding.point.x = border.point.x+style.border_width;
  padding.point.y = border.point.y+style.border_width;

  content.point.x = padding.point.x+style.left_padding;
  content.point.y = padding.point.y+style.top_padding ;
}


void
Box::
update_sizes()
{
  padding.width  = content.width +(style.left_padding+style.right_padding );
  padding.height = content.height+(style.top_padding +style.bottom_padding);

  border.width  = padding.width +(style.border_width*2);
  border.height = padding.height+(style.border_width*2);

  width  = border.width +(style.left_margin+style.right_margin );
  height = border.height+(style.top_margin +style.bottom_margin);
}


void
Box::
print() const
{
  printf("[widget] %s\n",name);

  printf("        point(%4d,%4d)\n",point.x,point.y);
  printf("content point(%4d,%4d)\n",content.point.x,content.point.y);
  printf("content  size(%4d,%4d)\n",content.width,content.height);
}


}




