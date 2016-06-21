#ifndef OAT_BUTTONMODULE_HPP
#define OAT_BUTTONMODULE_HPP




namespace oat{


class
ButtonModule
{
  int  index;
  int  flags;

  bool   test(int  flag) const{return(flags&flag);}
  void    set(int  flag){flags |=  flag;}
  void  unset(int  flag){flags &= ~flag;}

public:
  ButtonModule(): flags(0){}

  void  set_index(int  i)      ;
  int   get_index(      ) const;

  bool  test_pressing() const;
  bool  test_freezing() const;
  bool  test_pressed() const;
  bool  test_unpressed() const;
  bool  test_toggle() const;

  void    press();
  void  unpress();

  void    freeze();
  void  unfreeze();

  void    use_toggle();
  void  unuse_toggle();

  void  unset_shortlived();

  static void  unset_shortlived_all();

};


}




#endif




