#ifndef OAT_CROSS_HPP
#define OAT_CROSS_HPP


#include"oat_container.hpp"
#include"oat_icon.hpp"


namespace oat{


class
Cross: public Container
{
public:
  enum class Direction{
    up, left, right, down
  };

  using Callback = void  (*)(Cross&  cr, Direction  dir);

protected:
  Callback  callback;

public:
  Cross(Callback  cb=nullptr);

  void  set_callback(Callback  cb);

};


}




#endif




