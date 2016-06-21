#ifndef OAT_ARRAYMODULE_HPP
#define OAT_ARRAYMODULE_HPP


namespace oat{


template<typename  T>
class
ArrayModule
{
  T*  elements;

  Length  width ;
  Length  height;

public:
  using Element = T;

   ArrayModule():
   elements(nullptr),
   width(0),
   height(0){}

   ArrayModule(int  w, int  h):
   elements(nullptr),
   width(0),
   height(0){resize(w,h);}

   ArrayModule(      ArrayModule&&  rhs):
   elements(nullptr),
   width(0),
   height(0){*this = std::move(rhs);}

   ArrayModule(const ArrayModule&   rhs):
   elements(nullptr),
   width(0),
   height(0){*this = rhs;}

  virtual ~ArrayModule()
  {
    delete elements;
  }


  ArrayModule&  operator=(      ArrayModule&&  rhs)
  {
    width  = rhs.width ;
    height = rhs.height;

    elements = rhs.elements          ;
               rhs.elements = nullptr;

    return *this;
  }

  ArrayModule&  operator=(const ArrayModule&   rhs)
  {
    resize(rhs.width,rhs.height,rhs.elements);

    return *this;
  }

  void  resize(int  w, int  h, const T*  src=nullptr)
  {
    const int  oldlen = width*height;
          int  newlen = w*h;

      if(newlen > oldlen)
      {
        delete elements                ;
               elements = new T[newlen];
      }


      if(src)
      {
        auto  dst = elements;

          while(newlen--)
          {
            *dst++ = *src++;
          }
      }


    width  = w;
    height = h;
  }

  void  fill(const T&  src)
  {
    int  len = width*height;

    auto  dst = elements;

      while(len--)
      {
        *dst++ = src;
      }
  }

  Length  get_width()  const{return  width;}
  Length  get_height() const{return height;}

  T&  get_element(int  x, int  y) const{return elements[(width*y)+x];}

};


}




#endif




