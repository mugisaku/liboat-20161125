#ifndef FCFONT_COMBINEDSELECTOR_HPP_INCLUDED
#define FCFONT_COMBINEDSELECTOR_HPP_INCLUDED


#include"oat.hpp"
#include"fcfont.hpp"


using namespace oat;


namespace fcfont{


class
CombinedSelector: public Widget
{
public:
  using Callback = void  (*)(void*  ptr);

private:
  static constexpr int  x_element_number = 8;
  static constexpr int  y_element_number = 4;
  static constexpr int  element_width  = (Character::size  +10);
  static constexpr int  element_height = (Character::size*2+10);


  Point  cursor;

  Combined*  now;

  int  offset;

  Callback  callback;

  char16_t  buffer[16];

  void  update_buffer();

public:
  CombinedSelector(Callback  cb=nullptr);


  Combined*  get() const;

  const char16_t*  get_buffer() const;

  void    up();
  void  down();

  void  process_mouse(const Mouse&  mouse) override;

  void  render() override;

  static void  draw_combined(const Combined&  cmb, Widget*  wid, int  x, int  y);

};


}


#endif




