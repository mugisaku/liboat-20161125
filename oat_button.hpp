#ifndef OAT_BUTTON_HPP
#define OAT_BUTTON_HPP


#include"oat_icon.hpp"
#include"oat_text.hpp"
#include"oat_buttonmodule.hpp"


namespace oat{




class
Button: public Widget
{
public:
  using Callback = void  (*)(Button&  btn);

protected:
  ButtonModule  module;

  Widget**  icon_ptr;
  Widget**  text_ptr;

  Callback  callback;

public:
  Button(Text*  text=nullptr);
  Button(Icon*  icon, Text*  text=nullptr);


        ButtonModule&  get_module()            ;
  const ButtonModule&  get_const_module() const;

  const ButtonModule*  operator->() const;

  void  change_icon(Icon*  icon);
  void  change_text(Text*  text);

  void  set_callback(Callback  cb, bool  repeat=false);

  void  process_mouse(const Mouse&  mouse) override;
  void  process_when_mouse_left() override;

  void  render() override;

};




}




#endif




