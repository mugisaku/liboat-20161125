#ifndef OAT_DIAL_HPP
#define OAT_DIAL_HPP


#include"oat_widget.hpp"
#include"oat_button.hpp"
#include"oat_text.hpp"


namespace oat{


class
Dial: public Widget
{
public:
  using Callback = void  (*)(Dial&  dial, int  old_value);

private:
  Widget**  caption_ptr;

  Widget**  text_ptr;

  Widget**  down_button_ptr;
  Widget**    up_button_ptr;

  int  value_min;
  int  value_max;
  int  value    ;
  int  value_step;

  Callback  callback;

public:
  Dial(Widget*  caption, int  max, int  step=1, int  min=0);


  void  reset(int  max, int  step, int  min);

  void  set_callback(Callback  cb);

  void  change_value(int  v)      ;
  int      get_value(      ) const;

  void    up_value();
  void  down_value();
  
};


}




#endif




