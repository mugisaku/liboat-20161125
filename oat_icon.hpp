#ifndef OAT_ICON_HPP
#define OAT_ICON_HPP


#include"oat_widget.hpp"
#include"oat_iconmodule.hpp"


namespace oat{


class
Icon: public Widget
{
public:
  using Callback = void  (*)(Icon&  icon);

private:
  std::vector<const IconModule*>  modules;

  int  current;

  Callback  callback;

public:
  Icon(std::initializer_list<const IconModule*>  ls={});


  const IconModule&  get_module(int  i) const;

  void  change_current(int  i);

  const int&  get_current() const;

  void  set_callback(Callback  cb);

  void  process_mouse(const Mouse&  mouse) override;

  void  render() override;
  
};


}




#endif




