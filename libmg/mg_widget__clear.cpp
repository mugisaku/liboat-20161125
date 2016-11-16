#include"mg_widget.hpp"
#include"mg_core.hpp"



using namespace oat;


namespace{
void
clear(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::clear_chip();
    }
}
}


oat::Widget*
create_clear_widget()
{
  auto  btn = new Button(new Text(u"Clear"));

  btn->set_callback(clear);

  return btn;
}




