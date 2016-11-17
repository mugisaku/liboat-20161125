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


}




Widget*
create_manager_widget()
{
  auto  btn = new Button(new Text(u"PNGで保存"));

  btn->set_callback(save);

  return btn;
}





