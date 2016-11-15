#ifndef OAT_DIAL_HPP
#define OAT_DIAL_HPP


#include"oat_container.hpp"
#include"oat_button.hpp"
#include"oat_text.hpp"


namespace oat{


class
Dial: public Container
{
public:
  using Callback = void  (*)(Dial&  dial, int  old_value);

private:
  Widget*  caption;

  Text*  text;

  Button*  down_button;
  Button*    up_button;

  int  value_min;
  int  value_max;
  int  value    ;
  int  value_step;

  Callback  callback;

public:
  Dial(Widget*  caption_, int  max, int  step=1, int  min=0);


  void  reset(int  max, int  step, int  min);

  void  set_callback(Callback  cb);

  void  change_value_max(int  v);

  void  change_value(int  v)      ;
  int      get_value(      ) const;

  void    up_value();
  void  down_value();
  
};


}




#endif




