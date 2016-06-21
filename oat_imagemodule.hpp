#ifndef OAT_IMAGEMODULE_HPP
#define OAT_IMAGEMODULE_HPP


#include"oat_widget.hpp"
#include"oat_color.hpp"
#include"oat_arraymodule.hpp"
#include"oat_iconmodule.hpp"


namespace oat{


class
DirectColorImageModule: public ArrayModule<Color>
{
public:
  using Base = ArrayModule<Color>;

  DirectColorImageModule(){}
  DirectColorImageModule(int  w, int  h): Base(w,h){}
  DirectColorImageModule(      Base&&  rhs): Base(std::move(rhs)){}
  DirectColorImageModule(const Base&   rhs): Base(rhs){}

};


class
IndexColorImageModule: public ArrayModule<palette::index_t>
{
public:
  using Base = ArrayModule<palette::index_t>;

  IndexColorImageModule(){}
  IndexColorImageModule(int  w, int  h): Base(w,h){}
  IndexColorImageModule(      Base&&  rhs): Base(std::move(rhs)){}
  IndexColorImageModule(const Base&   rhs): Base(rhs){}

};


}




#endif




