#ifndef MG_CORE_HPP_INCLUDED
#define MG_CORE_HPP_INCLUDED


#include<cstdint>
#include"oat_widget.hpp"




struct
Frame
{
  int  x;
  int  y;
  int  w;
  int  h;

};




namespace core{


constexpr int  image_size = 384;


constexpr int            canvas_modified_flag = 1;
constexpr int     colorselector_modified_flag = 2;
constexpr int    patterndisplay_modified_flag = 4;
constexpr int  animationdisplay_modified_flag = 8;



void  set_parameter(int  chip_width_, int  chip_height_, int  chip_number_);

void  set_modified_flag(int  flag);
int   get_modified_flags();

void  update_because_of_image_changed();


void  change_tool_index(int  v);
int  get_tool_index();


void  change_chip_index(int  v);

int  get_chip_width();
int  get_chip_height();
int  get_chip_index();
int  get_chip_number();


void   copy_chip();
void  paste_chip(bool  overwrite);
void  reverse_chip_horizontally();
void  reverse_chip_vertically();
void  mirror_chip_vertically();
void  shift_chip_up();
void  shift_chip_left();
void  shift_chip_right();
void  shift_chip_down();
void  clear_chip();

const Frame&  get_frame();

void  change_frame_point(const oat::Point&  pt);


void  change_color_index(int  v);
int  get_color_index();

void  set_palette_gray(int  i, uint8_t  l);
void   set_palette_rgb(int  i, uint8_t  r, uint8_t  g, uint8_t  b);

void     fill_area(int  color_index_, int  x, int  y);
void     put_pixel(int  color_index_, int  x, int  y);
int  get_image_pixel(int  x, int  y);
int  get_chip_pixel(int  x, int  y);
int  get_frame_pixel(int  x, int  y);


const char*  get_filepath();

void   read(const char*  path);
void  write();


}



#endif




