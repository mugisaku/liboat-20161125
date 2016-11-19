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
      core::paste_chip(true);
    }
}


void
layer(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::paste_chip(false);
    }
}


void
reverse_horizontally(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::reverse_chip_horizontally();
    }
}


void
reverse_vertically(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::reverse_chip_vertically();
    }
}


void
mirror_vertically(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::mirror_chip_vertically();
    }
}


void
shift_up(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::shift_chip_up();
    }
}


void
shift_left(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::shift_chip_left();
    }
}


void
shift_right(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::shift_chip_right();
    }
}


void
shift_down(Button&  btn)
{
    if(btn->test_unpressed())
    {
      core::shift_chip_down();
    }
}
}


oat::Widget*
create_edit_widget()
{
  auto  cpy_btn = new Button(new Text(u"コピー"),copy);
  auto  pst_btn = new Button(new Text(u"貼り付け"),paste);
  auto  lay_btn = new Button(new Text(u"重ね貼り"),layer);
  auto  clr_btn = new Button(new Text(u"クリア"),clear);

  auto  rvh_btn = new Button(new Text(u"水平反転"),reverse_horizontally);
  auto  rvv_btn = new Button(new Text(u"垂直反転"),reverse_vertically);
  auto  mrv_btn = new Button(new Text(u"垂直鏡像"),mirror_vertically);


  auto  shu_btn = new Button(new Text(u"上へ"),shift_up);
  auto  shl_btn = new Button(new Text(u"左へ"),shift_left);
  auto  shr_btn = new Button(new Text(u"右へ"),shift_right);
  auto  shd_btn = new Button(new Text(u"下へ"),shift_down);

  return new TableColumn({new TableRow({cpy_btn,pst_btn,lay_btn,clr_btn}),
                          new TableRow({rvh_btn,rvv_btn,mrv_btn}),
                          new TableRow({new Text(u"シフト"),shu_btn,shl_btn,shr_btn,shd_btn}),
                        });
}




