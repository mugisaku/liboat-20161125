#ifndef OAT_TABLE_HPP
#define OAT_TABLE_HPP


#include"oat_widget.hpp"
#include<initializer_list>


namespace oat{


class
TableElement: public Widget
{
protected:
  Point  relative_tail_point;

  virtual void  append(Widget*  child) = 0;

public:
  void  append(std::initializer_list<Widget*>  ls);

};


class
TableRow: public TableElement
{
public:
  TableRow(std::initializer_list<Widget*>  children={});

  void  append(Widget*  child) override;

};


class
TableColumn: public TableElement
{
public:
  TableColumn(std::initializer_list<Widget*>  children={});

  void  append(Widget*  child) override;

};


}




#endif




