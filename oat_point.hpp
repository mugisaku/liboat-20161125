#ifndef OAT_POINT_HPP
#define OAT_POINT_HPP


#include<cstdlib>
#include<algorithm>


namespace oat{


using Position = int;
using Length   = int;


struct
Point
{
  Position  x;
  Position  y;

  constexpr Point(Position  x_=0, Position  y_=0):
  x(x_),
  y(y_){}


  void  reset(int  x_=0, int  y_=0)
  {
    x = x_;
    y = y_;
  }


  constexpr Point  operator+(const Point&  rhs) const
  {
    return Point(x+rhs.x,y+rhs.y);
  }


  constexpr Point  operator-(const Point&  rhs) const
  {
    return Point(x-rhs.x,y-rhs.y);
  }


  constexpr bool  operator==(const Point&  rhs) const
  {
    return((x == rhs.x) &&
           (y == rhs.y));
  }


  constexpr bool  operator!=(const Point&  rhs) const
  {
    return((x != rhs.x) ||
           (y != rhs.y));
  }


  Point&  operator=(const Point&  rhs)
  {
    x = rhs.x;
    y = rhs.y;

    return *this;
  }


  Point&  operator+=(const Point&  rhs)
  {
    x += rhs.x;
    y += rhs.y;

    return *this;
  }

};


struct
Rectangle
{
  Point  point;

  Length  width ;
  Length  height;

  constexpr Rectangle(int  x=0, int  y=0, int  w=0, int  h=0):
  point(x,y),
  width(w),
  height(h){}

  Rectangle(const Point&  a, const Point&  b):
  point( std::min(a.x,b.x),std::min(a.y,b.y)),
  width( std::abs(a.x-b.x)),
  height(std::abs(a.y-b.y)){}

  constexpr int  get_right()  const{return(point.x+width -1);}
  constexpr int  get_bottom() const{return(point.y+height-1);}

  constexpr bool  test(const Point&  pt) const
  {
    return((pt.x >= point.x) &&
           (pt.y >= point.y) &&
           (pt.x <  (point.x+width )) &&
           (pt.y <  (point.y+height)));
  }


  bool  grab(Point&  target) const
  {
    bool  flag = false;

      if(target.x <= point.x)
      {
        target.x = point.x;

        flag = true;
      }

    else
      if(target.x >= (point.x+width))
      {
        target.x = (point.x+width-1);

        flag = true;
      }


      if(target.y <= point.y)
      {
        target.y = point.y;

        flag = true;
      }

    else
      if(target.y >= (point.y+height))
      {
        target.y = (point.y+height-1);

        flag = true;
      }


    return flag;
  }

};


}


#endif




