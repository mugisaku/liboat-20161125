#ifndef MG_CORE_HPP_INCLUDED
#define MG_CORE_HPP_INCLUDED


#include<cstdint>
#include"oat_widget.hpp"




namespace core{


void  set_parameter(int  chip_width_, int  chip_height_, int  chip_number_);

void  set_canvas_updater(oat::WidgetUpdater  upd);
void  set_colorselector_updater(oat::WidgetUpdater  upd);
void  set_patterndisplay_updater(oat::WidgetUpdater  upd);
void  set_animationdisplay_updater(oat::WidgetUpdater  upd);
void  set_dial_updater(oat::WidgetUpdater  upd);


void  change_tool_index(int  v);
int  get_tool_index();


int  get_chip_width();
int  get_chip_height();
int  get_chip_number();

int  get_image_width();
int  get_image_height();

int  extend();

void  clear_chip();

void  move_x_offset(int  v);
void  move_y_offset(int  v);


int  get_x_offset();
int  get_y_offset();


void  change_color_index(int  v);
int  get_color_index();

void  set_palette_gray(int  i, uint8_t  l);
void   set_palette_rgb(int  i, uint8_t  r, uint8_t  g, uint8_t  b);

void     fill_area(int  color_index_, int  x, int  y);
void     put_pixel(int  color_index_, int  x, int  y);
int  get_image_pixel(int  x, int  y);
int  get_chip_pixel(int  x, int  y);
int  get_segment_pixel(int  x, int  y);

void   read(const char*  path);
void  write(const char*  path);


}



#endif




