#include"oat_checkform.hpp"
#include"oat.hpp"
#include<algorithm>




namespace oat{




CheckForm::
CheckForm(std::initializer_list<Widget*>  ls):
last_index(-1),
callback(nullptr)
{
  TableElement::append(ls);
}


CheckForm::
~CheckForm()
{
    for(auto  ptr: members)
    {
      delete ptr;
    }
}




void
CheckForm::
set_callback(Callback  cb)
{
  callback = cb;
}


const CheckForm::Member&
CheckForm::
get_member(int  i) const
{
  return *members[i];
}




void
CheckForm::
append_child(Widget*  child, const IconModule&  a, const IconModule&  b)
{
    if(child)
    {
      int  i = children.size();

      auto  ico = new Icon({&a,&b});

      members.emplace_back(new PerfectMember(i,*this,ico,child));

      TableColumn::append(new TableRow({ico,child}));
    }
}



void
CheckForm::
append(Widget*  child)
{
  append_child(child,const_icon::offcheck,const_icon::oncheck);
}


void
CheckForm::
process_mouse(const Mouse&  mouse)
{
    if(callback && mouse.left.test_unpressed())
    {
        for(auto  m: members)
        {
          auto  res = m->icon->scan(mouse.point);

            if(!res)
            {
              res = m->widget->scan(mouse.point);
            }


            if(res)
            {
              auto  icon = m->icon;

                if(last_index < 0)
                {
                    if(icon->get_current() == 0){icon->change_current(1);}
                  else                          {icon->change_current(0);}

                  callback(*m);

                  return;
                }


                if(last_index != m->index)
                {
                  icon->change_current(1);

                  callback(*m);


                  auto&  last = *members[last_index];

                  last.icon->change_current(0);

                  callback(last);
                }


              last_index = m->index;

              return;
            }
        }
    }
}




RadioForm::
RadioForm(std::initializer_list<Widget*>  ls, int  initial_i)
{
  TableElement::append(ls);

  last_index = initial_i;

  members[initial_i]->icon->change_current(1);
}


void
RadioForm::
append(Widget*  child)
{
  append_child(child,const_icon::offradio,const_icon::onradio);
}




}




