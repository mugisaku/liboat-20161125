#include"fcfont_editor.hpp"
#include"fcfont_sample.hpp"
#include"fcfont_charactereditor.hpp"
#include"fcfont_characterselector.hpp"
#include"fcfont_combinedselector.hpp"


using namespace oat;


namespace fcfont{


void
Editor::
chr_up(Button&  btn)
{
  auto&  ed = *static_cast<Editor*>(btn.get_userdata());

    if(btn->test_pressed())
    {
      ed.chr_selector->up();
    }
}


void
Editor::
chr_down(Button&  btn)
{
  auto&  ed = *static_cast<Editor*>(btn.get_userdata());

    if(btn->test_pressed())
    {
      ed.chr_selector->down();
    }
}


void
Editor::
cmb_up(Button&  btn)
{
  auto&  ed = *static_cast<Editor*>(btn.get_userdata());

    if(btn->test_pressed())
    {
      ed.cmb_selector->up();
    }
}


void
Editor::
cmb_down(Button&  btn)
{
  auto&  ed = *static_cast<Editor*>(btn.get_userdata());

    if(btn->test_pressed())
    {
      ed.cmb_selector->down();
    }
}


namespace{
void
save(Button&  btn)
{
    if(btn.get_module().test_unpressed())
    {
      static int  n;

      char  buf[256];

      snprintf(buf,sizeof(buf),"__FCFONT_%03d.txt",n++);

      auto  f = fopen(buf,"wb");

        if(f)
        {
          Character::print_table(f);
          Character::print_table();
           Combined::print_table(f);
           Combined::print_table();

          fclose(f);
        }
    }
}
}


void
Editor::
chr_update(void*  ptr)
{
  auto&  ed = *static_cast<Editor*>(ptr);

  ed.chr_cp_text->change_string(ed.chr_selector->get_buffer());

  ed.chr_editor->need_to_redraw();
}


void
Editor::
cmb_update(void*  ptr)
{
  auto&  ed = *static_cast<Editor*>(ptr);

  ed.cmb_cp_text->change_string(ed.cmb_selector->get_buffer());

  ed.sample->change(ed.cmb_selector->get()->unicode);
}


void
Editor::
change_upper(Button&  btn)
{
    if(btn.get_module().test_pressing())
    {
      auto&  ed = *static_cast<Editor*>(btn.get_userdata());

      auto&  c = *ed.cmb_selector->get();

      c.upper = ed.chr_selector->get()->unicode;

      ed.cmb_selector->need_to_redraw();
    }
}


void
Editor::
change_lower(Button&  btn)
{
    if(btn.get_module().test_pressing())
    {
      auto&  ed = *static_cast<Editor*>(btn.get_userdata());

      auto&  c = *ed.cmb_selector->get();

      c.lower = ed.chr_selector->get()->unicode;

      ed.cmb_selector->need_to_redraw();
    }
}




Editor::
Editor()
{
  chr_cp_text = new Text(u"? U+XXXX");
  cmb_cp_text = new Text(u"? U+XXXX");

    chr_up_button = new Button(new Icon({&const_icon::up}));
  chr_down_button = new Button(new Icon({&const_icon::down}));

    chr_up_button->set_callback(  chr_up);
  chr_down_button->set_callback(chr_down);

    chr_up_button->set_userdata(this);
  chr_down_button->set_userdata(this);


    cmb_up_button = new Button(new Icon({&const_icon::up}));
  cmb_down_button = new Button(new Icon({&const_icon::down}));

    cmb_up_button->set_callback(  cmb_up);
  cmb_down_button->set_callback(cmb_down);

    cmb_up_button->set_userdata(this);
  cmb_down_button->set_userdata(this);


  save_button = new Button(new Text(u"Save"));
  save_button->set_callback(save);


  auto  chr_row = new TableRow({chr_up_button,chr_down_button});

  chr_selector = new CharacterSelector(chr_update);

  chr_selector->set_userdata(this);


  upper_button = new Button(new Text(u"上部を変更"));
  lower_button = new Button(new Text(u"下部を変更"));

  upper_button->set_callback(change_upper);
  lower_button->set_callback(change_lower);
  upper_button->set_userdata(this);
  lower_button->set_userdata(this);


  auto  cmb_row = new TableRow({cmb_up_button,cmb_down_button});

  cmb_selector = new CombinedSelector(cmb_update);

  cmb_selector->set_userdata(this);


  chr_editor = new CharacterEditor(*chr_selector,*cmb_selector,*col_selector);


  sample = new Sample;


  auto  a_tbl = new TableColumn({chr_editor,chr_cp_text});
  auto  b_tbl = new TableColumn({new Text(u"基本文字"),chr_selector,chr_row});
  auto  c_tbl = new TableColumn({new TableColumn({upper_button,lower_button}),cmb_cp_text});
  auto  d_tbl = new TableColumn({new Text(u"合体文字"),cmb_selector,cmb_row});

  join(new TableColumn({new TableRow({a_tbl,b_tbl,c_tbl,d_tbl}),new TableRow({sample,save_button})}),0,0);
}




}




