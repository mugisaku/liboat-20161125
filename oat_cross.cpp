#include"oat_cross.hpp"
#include"oat_icon.hpp"
#include"oat.hpp"




namespace oat{




namespace{
void
up_cb(Button&  btn)
{
}


void
left_cb(Button&  btn)
{
}


void
right_cb(Button&  btn)
{
}


void
down_cb(Button&  btn)
{
}


}


Cross::
Cross(Callback  cb):
callback(cb)
{
  auto     up_btn = new Button(new Icon({&const_icon::up   }),   up_cb);
  auto   left_btn = new Button(new Icon({&const_icon::left }), left_cb);
  auto   down_btn = new Button(new Icon({&const_icon::down }), down_cb);
  auto  right_btn = new Button(new Icon({&const_icon::right}),right_cb);

     up_btn->set_userdata(this);
   left_btn->set_userdata(this);
   down_btn->set_userdata(this);
  right_btn->set_userdata(this);


  constexpr int  unit = 36;

  join(   up_btn,unit  ,   0);
  join( left_btn,     0,unit);
  join( down_btn,unit  ,unit);
  join(right_btn,unit*2,unit);
}




void
Cross::
set_callback(Callback  cb)
{
  callback = cb;
}




}




