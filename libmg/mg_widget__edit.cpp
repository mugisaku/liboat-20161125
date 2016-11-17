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


void
copy(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::copy_chip();
    }
}


void
paste(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::paste_chip();
    }
}
}


oat::Widget*
create_edit_widget()
{
  auto  cpy_btn = new Button(new Text(u"Copy"));
  auto  pst_btn = new Button(new Text(u"Paste"));
  auto  clr_btn = new Button(new Text(u"Clear"));

  cpy_btn->set_callback(copy);
  pst_btn->set_callback(paste);
  clr_btn->set_callback(clear);

  return new TableColumn({cpy_btn,pst_btn,clr_btn});
}




