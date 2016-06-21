#ifndef OAT_IMAGE_HPP
#define OAT_IMAGE_HPP


#include"oat_widget.hpp"
#include"oat_imagemodule.hpp"


namespace oat{


class
Image: public Widget
{
protected:
  Length  pixel_size;

  Point  view_point;

  Length  view_width ;
  Length  view_height;

  void  update_size();

public:
  Image(int  pixel_size_=1, int  view_w=0, int  view_h=0);


  void  clear();

  void   change_view_size(int  w, int  h);
  void  change_pixel_size(int  n);

  const Point&  get_view_point() const;

  virtual const Color&  get_color(int  x, int  y) const=0;

  void  render() override;

};


class
DirectColorImage: public Image
{
protected:
  DirectColorImageModule  module;

public:
  DirectColorImage();
  DirectColorImage(DirectColorImageModule&&  m, int  pixel_size_=1, int  view_w=0, int  view_h=0);


        DirectColorImageModule&  get_module();
  const DirectColorImageModule&  get_const_module() const;

  void  clear();

  void  reset_module(DirectColorImageModule&&  m);

        Color&  get_color(int  x, int  y)               ;
  const Color&  get_color(int  x, int  y) const override;

};


class
IndexColorImage: public Image
{
protected:
	  IndexColorImageModule  module;

public:
  IndexColorImage();
  IndexColorImage(IndexColorImageModule&&  m, int  pixel_size_=1, int  view_w=0, int  view_h=0);


        IndexColorImageModule&  get_module();
  const IndexColorImageModule&  get_const_module() const;

  void  clear();

  void  reset_module(IndexColorImageModule&&  m);

  const Color&  get_color(int  x, int  y) const override;

  palette::index_t&  get_index(int  x, int  y) const;

};


}




#endif




