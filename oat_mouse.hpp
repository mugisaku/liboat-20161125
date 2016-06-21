#ifndef OAT_MOUSE_HPP
#define OAT_MOUSE_HPP


#include"oat_point.hpp"
#include"oat_buttonmodule.hpp"


namespace oat{




struct
Mouse
{
  Point           point;
  Point  previous_point;

  ButtonModule   left;
  ButtonModule  right;

  void  change_point(const Point&  new_point)
  {
    previous_point = point            ;
                     point = new_point;
  }


  bool  test_moved() const
  {
    return(point != previous_point);
  }

};




}




#endif




