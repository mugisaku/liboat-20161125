#include"mg_widget.hpp"
#include"mg_core.hpp"




using namespace oat;


namespace{
void
save(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::write();
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





