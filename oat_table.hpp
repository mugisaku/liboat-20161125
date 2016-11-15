#ifndef OAT_TABLE_HPP
#define OAT_TABLE_HPP


#include"oat_container.hpp"
#include<initializer_list>


namespace oat{


class
TableElement: public Container
{
protected:
  Point  relative_tail_point;

  virtual void  append(Widget*  child) = 0;

public:
  void  append(std::initializer_list<Widget*>  ls);
  void  append(std::vector<Widget*>  ls);

};


class
TableRow: public TableElement
{
public:
  TableRow(std::initializer_list<Widget*>  children={});
  TableRow(std::vector<Widget*>  children);

  void  append(Widget*  child) override;

};


class
TableColumn: public TableElement
{
public:
  TableColumn(std::initializer_list<Widget*>  children={});
  TableColumn(std::vector<Widget*>  children);

  void  append(Widget*  child) override;

};


}




#endif




