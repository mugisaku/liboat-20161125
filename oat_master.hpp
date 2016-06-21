#ifndef OAT_MASTER_HPP
#define OAT_MASTER_HPP


#include"oat_imagemodule.hpp"


namespace oat{


class
Master final: public Widget
{
  DirectColorImageModule  module;

  Widget*  current;

public:
  Master();


  void  change_dragging(bool  v);

  void  process(Mouse&  mouse);

  bool  update();

  Color&  get_pixel(int  x, int  y) const;

  const DirectColorImageModule&  get_module() const;

};


}




#endif




