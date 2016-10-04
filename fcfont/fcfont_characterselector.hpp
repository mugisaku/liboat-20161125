#ifndef FCFONT_CHARACTERSELECTOR_HPP_INCLUDED
#define FCFONT_CHARACTERSELECTOR_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


class
CharacterSelector: public Widget
{
public:
  using Callback = void  (*)(void*  userdata);

private:
  static constexpr int  x_element_number = 8;
  static constexpr int  y_element_number = 8;
  static constexpr int  element_width = (Character::size+10);


  Point  cursor;

  Character*  now;

  int  offset;

  char16_t  buffer[16];

  Callback  callback;

  void  update_buffer();

public:
  CharacterSelector(Callback  cb=nullptr);


  Character*  get() const;

  const char16_t*  get_buffer() const;

  void    up();
  void  down();

  void  process_mouse(const Mouse&  mouse) override;
  void  render() override;

  static void  draw_character(const Character&  c, Widget*  wid, int  x_base, int  y_base);

};


}


#endif




