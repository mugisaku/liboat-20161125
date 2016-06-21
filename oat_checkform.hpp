#ifndef OAT_CHECKFORM_HPP
#define OAT_CHECKFORM_HPP


#include"oat_table.hpp"
#include"oat_icon.hpp"


namespace oat{


class
CheckForm: public TableColumn
{
public:
  struct Member{
    const int  index;

    const int&  current;

    Member(int  i, const int&  c):
    index(i), current(c){}

  };


  using Callback = void  (*)(Member&  member);

protected:
  struct PerfectMember: public Member{
    CheckForm&  form;

    Icon*  icon;

    Widget*  widget;

    PerfectMember(int  i, CheckForm&  f, Icon*  ico, Widget*  w):
    Member(i,ico->get_current()),
    form(f), icon(ico), widget(w){}

  };


  int  last_index;

  std::vector<PerfectMember*>  members;

  Callback  callback;

  static void  icon_callback(Icon&  icon);

  void  append_child(Widget*  child, const IconModule&  a, const IconModule&  b);

public:
  CheckForm(std::initializer_list<Widget*>  ls={});
  ~CheckForm();


  const Member&  get_member(int  i) const;

  void  set_callback(Callback  cb);

  void  append(Widget*  child) override;

  void  process_mouse(const Mouse&  mouse) override;

};


class
RadioForm: public CheckForm
{
public:
  RadioForm(std::initializer_list<Widget*>  ls, int  initial_i=0);


  void  append(Widget*  child) override;

};


}




#endif




