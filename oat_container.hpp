#ifndef OAT_CONTAINER_HPP
#define OAT_CONTAINER_HPP


#include<list>
#include"oat_widget.hpp"




namespace oat{


class
Container: public Widget
{
protected:
  void  redraw() override;
  void  redraw_perfect() override;

  void  reform() override;

  std::list<Widget*>  children;

public:
  ~Container() override;


  void  join(Widget*  child, int  x, int  y);

  void  update_sizes() override;

  Widget*  scan(const Point&  pt) override;

  void  process_mouse(const Mouse&  mouse) override;

  void  process_when_mouse_entered() override;
  void  process_when_mouse_left() override;

  void  render() override;

};


}


#endif




