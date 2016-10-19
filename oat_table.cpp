#include"oat_table.hpp"




namespace oat{




void
TableElement::
append(std::initializer_list<Widget*>  ls)
{
    for(auto  child: ls)
    {
      append(child);
    }
}


void
TableElement::
append(std::vector<Widget*>  ls)
{
    for(auto  child: ls)
    {
      append(child);
    }
}




TableRow::
TableRow(std::initializer_list<Widget*>  children)
{
  TableElement::append(children);
}


TableRow::
TableRow(std::vector<Widget*>  children)
{
  TableElement::append(children);
}


void
TableRow::
append(Widget*  child)
{
    if(child)
    {
      join(child,relative_tail_point.x,relative_tail_point.y);

      child->update_sizes();

      relative_tail_point.x += child->width;
    }
}




TableColumn::
TableColumn(std::initializer_list<Widget*>  children)
{
  TableElement::append(children);
}


TableColumn::
TableColumn(std::vector<Widget*>  children)
{
  TableElement::append(children);
}




void
TableColumn::
append(Widget*  child)
{
    if(child)
    {
      join(child,relative_tail_point.x,relative_tail_point.y);

      child->update_sizes();

      relative_tail_point.y += child->height;
    }
}




}




