#include"mg_widget.hpp"
#include"mg_core.hpp"




using namespace oat;


namespace{
void
save(Button&  btn)
{
    if(btn->test_unpressed())
    {
      static int  n;

      char  buf[256];

      snprintf(buf,sizeof(buf),"__PTRN%03d.png",n++);

      core::write(buf);
    }
}


void
append_new(Button&  btn)
{
    if(btn->test_unpressed())
    {
      auto  v = core::extend();

      auto  dial = static_cast<Dial*>(btn.get_userdata());

      dial->change_value_max(v);
    }
}


void
change(Dial&  d, int  old_value)
{
  core::move_y_offset(d.get_value()-1);
}


void
update_dial(Widget&  w)
{
  static_cast<Dial&>(w).reset(core::get_image_height()/core::get_chip_height(),1,1);
}
}




Widget*
create_manager_widget()
{
  auto  dial = new Dial(nullptr,1,1,1);

  dial->set_callback(change);

  core::set_dial_updater(WidgetUpdater(dial,update_dial));

  auto  save_btn = new Button(new Text(u"PNGで保存"));
  auto  appn_btn = new Button(new Text(u"新規追加"));

  save_btn->set_callback(save);
  appn_btn->set_callback(append_new);
  appn_btn->set_userdata(dial);
  

  auto  tbl = new TableColumn({new TableRow({dial,appn_btn}),save_btn});

  return tbl;
}





