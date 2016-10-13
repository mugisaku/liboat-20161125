#include"fcfont_charactereditor.hpp"
#include"fcfont_characterselector.hpp"
#include"fcfont_combinedselector.hpp"


using namespace oat;


namespace fcfont{


CharacterEditor::
CharacterEditor(CharacterSelector&  chrsel_, CombinedSelector&  cmbsel_):
chrsel(chrsel_),
cmbsel(cmbsel_)
{
  style.background_color = const_color::black;

  change_content_width( pixel_size*Character::size);
  change_content_height(pixel_size*Character::size);
}




void
CharacterEditor::
process_mouse(const Mouse&  mouse)
{
  cursor = get_mouse_point(mouse);

  cursor.x = cursor.x/pixel_size;
  cursor.y = cursor.y/pixel_size;

  auto&  target = chrsel.get()->data[cursor.y];

  auto  flag = (0x4000>>(cursor.x<<1));

    if(mouse.left.test_pressing())
    {
      target |= flag;

      chrsel.need_to_redraw();
      cmbsel.need_to_redraw();
    }

  else
    if(mouse.right.test_pressing())
    {
      target &= ~flag;

      chrsel.need_to_redraw();
      cmbsel.need_to_redraw();
    }


  need_to_redraw();
}


void
CharacterEditor::
render()
{
  auto  pt = content.point;

  fill();

  auto  src = chrsel.get()->data;

    for(int  y = 0;  y < Character::size;  ++y)
    {
      auto  code = *src++;

        for(int  x = 0;  x < Character::size;  ++x)
        {
          fill_rect(Character::color_table[code>>14],pt.x+(pixel_size*x),pt.y+(pixel_size*y),pixel_size,pixel_size);

          code <<= 2;
        }
    }
}



}




