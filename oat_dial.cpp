#include"oat_dial.hpp"
#include<algorithm>




namespace oat{


namespace{


const char*
const  format = "%4d/%4d";


void
down_value_(Button&  btn)
{
    if(btn.get_const_module().test_pressed())
    {
      auto&  d = *static_cast<Dial*>(btn.get_userdata());

      d.down_value();
    }
}


void
up_value_(Button&  btn)
{
    if(btn.get_const_module().test_pressed())
    {
      auto&  d = *static_cast<Dial*>(btn.get_userdata());

      d.up_value();
    }
}


}



Dial::
Dial(Widget*  caption, int  max, int  step, int  min):
value(min),
callback(nullptr)
{
  int  tail = 0;

    if(caption)
    {
      caption->update_sizes();

      tail = caption->width;
    }


  caption_ptr = &join(caption,0,0);

  text_ptr = &join(new Text(u"xxxx/xxxx"),tail,0);


  (*text_ptr)->update_sizes();

  tail += (*text_ptr)->width;

  auto  down_button = new Button(new Icon({&const_icon::left }));
  auto    up_button = new Button(new Icon({&const_icon::right}));



  down_button_ptr = &join(down_button,tail,0);

  down_button->update_sizes();

  tail += down_button->width;

  up_button_ptr = &join(up_button,tail,0);


  down_button->set_callback(down_value_);
    up_button->set_callback(  up_value_);

  down_button->set_userdata(this);
    up_button->set_userdata(this);

  reset(max,step,min);

  change_value(min);
}




void
Dial::
reset(int  max, int  step, int  min)
{
  int  old_value = value;

  value_max = max;
  value_min = min;
  value_step = step;

  change_value(value);
}


void
Dial::
set_callback(Callback  cb)
{
  callback = cb;
}


void
Dial::
change_value(int  v)
{
  const int  old_value = value                                            ;
                         value = std::min(value_max,std::max(value_min,v));

    if(callback)
    {
      callback(*this,old_value);
    }


  char  buf[256];

  snprintf(buf,sizeof(buf),format,value,value_max);

  static_cast<Text*>(*text_ptr)->change_string(buf);

  need_to_redraw();
}


int
Dial::
get_value() const
{
  return value;
}


void
Dial::
up_value()
{
  change_value(value+value_step);
}


void
Dial::
down_value()
{
  change_value(value-value_step);
}


}




