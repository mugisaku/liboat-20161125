#ifndef OAT_BUTTON_HPP
#define OAT_BUTTON_HPP


#include"oat_icon.hpp"
#include"oat_text.hpp"
#include"oat_container.hpp"
#include"oat_buttonmodule.hpp"


namespace oat{




class
Button: public Container
{
public:
  using Callback = void  (*)(Button&  btn);

protected:
  ButtonModule  module;

  Callback  callback;

public:
  Button(Widget*  child=nullptr, Callback  cb=nullptr);


        ButtonModule&  get_module()            ;
  const ButtonModule&  get_const_module() const;

  const ButtonModule*  operator->() const;

  void  change_child(Widget*  child);

  void    press();
  void  unpress();

  void  set_callback(Callback  cb, bool  repeat=false);

  void  process_mouse(const Mouse&  mouse) override;
  void  process_when_mouse_left() override;

  void  render() override;

};




}




#endif




