#include"mg_core.hpp"
#include"mg_colorselector.hpp"
#include"oat_widget.hpp"
#include<cstring>
#include<cstdio>
#include<vector>
#include<libpng/png.h>
#include<zlib.h>




namespace core{


namespace{


oat::WidgetUpdater      cv_updater;
oat::WidgetUpdater  colsel_updater;
oat::WidgetUpdater  ptndsp_updater;
oat::WidgetUpdater  anidsp_updater;


int  chip_width;
int  chip_height;
int  chip_number;

int  color_index;


int  color_type;

int  depth;

std::vector<png_color>  palette;

int  tool_index;
int  chip_index;


std::vector<uint8_t>
copy_buffer;


uint8_t
pixels[image_size][image_size];


Frame
frame;




bool
table[80][80];


void
search(int  color_index_, int  target, int  x, int  y)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

        if(get_chip_pixel(x,y) == target)
        {
          put_pixel(color_index_,x,y);

            if(x                  ){search(color_index_,target,x-1,y  );}
            if(y                  ){search(color_index_,target,x  ,y-1);}
            if(x < (chip_width -1)){search(color_index_,target,x+1,y  );}
            if(y < (chip_height-1)){search(color_index_,target,x  ,y+1);}
        }
    }
}




void
close_read(png_structp  png, png_infop  png_info, FILE*  f)
{
  png_read_end(png,png_info);
  png_destroy_read_struct(&png,&png_info,nullptr);

  fclose(f);
}

void
close_write(png_structp  png, png_infop  png_info, FILE*  f)
{
  png_write_end(png,png_info);
  png_destroy_write_struct(&png,&png_info);

  fclose(f);
}




void
reset_palette()
{
  palette.resize(color_number*2);

  set_palette_gray( 0,0x1F);
  set_palette_gray( 1,0x3F);
  set_palette_gray( 2,0x5F);
  set_palette_gray( 3,0x7F);
  set_palette_gray( 4,0x9F);
  set_palette_gray( 5,0xBF);
  set_palette_gray( 6,0xDF);
  set_palette_gray( 7,0xFF);
  set_palette_gray( 8,0x1F);
  set_palette_gray( 9,0x3F);
  set_palette_gray(10,0x5F);
  set_palette_gray(11,0x7F);
  set_palette_gray(12,0x9F);
  set_palette_gray(13,0xBF);
  set_palette_gray(14,0xDF);
  set_palette_gray(15,0xFF);
}




}


void
set_parameter(int  chip_width_, int  chip_height_, int  chip_number_)
{
  chip_width  = chip_width_;
  chip_height = chip_height_;
  chip_number = chip_number_;

  frame.x = 0;
  frame.y = 0;
  frame.w = chip_width*chip_number;
  frame.h = chip_height;

  reset_palette();
}


void  set_canvas_updater(oat::WidgetUpdater  upd){cv_updater = upd;}
void  set_colorselector_updater(oat::WidgetUpdater  upd){colsel_updater = upd;}
void  set_patterndisplay_updater(oat::WidgetUpdater  upd){ptndsp_updater = upd;}
void  set_animationdisplay_updater(oat::WidgetUpdater  upd){anidsp_updater = upd;}




void
change_chip_index(int  v)
{
  chip_index = v;
}


int  get_chip_width(){return chip_width;}
int  get_chip_height(){return chip_height;}
int  get_chip_index(){return chip_index;}
int  get_chip_number(){return chip_number;}




const Frame&
get_frame()
{
  return frame;
}


void
change_frame_point(const oat::Point&  pt)
{
  frame.x = pt.x;
  frame.y = pt.y;

   cv_updater();
  ptndsp_updater();
}




void  change_tool_index(int  v){tool_index = v;}
int  get_tool_index(){return tool_index;}


void
change_color_index(int  v)
{
  color_index = v;

  colsel_updater();
}


int
get_color_index()
{
  return color_index;
}




void
copy_chip()
{
  copy_buffer.clear();

    for(int  y = 0;  y < chip_height;  ++y){
    for(int  x = 0;  x < chip_width ;  ++x){
      copy_buffer.emplace_back(get_chip_pixel(x,y));
    }}
}


void
paste_chip()
{
    if(copy_buffer.size())
    {
      auto  it = copy_buffer.cbegin();

        for(int  y = 0;  y < chip_height;  ++y){
        for(int  x = 0;  x < chip_width ;  ++x){
          put_pixel(*it++,x,y);
        }}


          cv_updater();
      ptndsp_updater();
    }
}


void
clear_chip()
{
    for(int  y = 0;  y < chip_height;  ++y){
    for(int  x = 0;  x < chip_width ;  ++x){
      put_pixel(0,x,y);
    }}


      cv_updater();
  ptndsp_updater();
}




void
set_palette_gray(int  i, uint8_t  l)
{
  palette[i].red   = l;
  palette[i].green = l;
  palette[i].blue  = l;
}


void
set_palette_rgb(int  i, uint8_t  r, uint8_t  g, uint8_t  b)
{
  palette[i].red   = r;
  palette[i].green = g;
  palette[i].blue  = b;
}


void
fill_area(int  color_index_, int  x, int  y)
{
  auto  target = get_chip_pixel(x,y);

    if(target != color_index_)
    {
      std::memset(&table,0,sizeof(table));

      search(color_index_,target,x,y);

       cv_updater();
      ptndsp_updater();
    }
}


void
put_pixel(int  color_index_, int  x, int  y)
{
  pixels[frame.y+y][frame.x+(chip_width*chip_index)+x] = color_index_;

   cv_updater();
  ptndsp_updater();
}


int
get_image_pixel(int  x, int  y)
{
  return pixels[y][x];
}


int
get_chip_pixel(int  x, int  y)
{
  return get_image_pixel(frame.x+(chip_width*chip_index)+x,frame.y+y);
}


int
get_frame_pixel(int  x, int  y)
{
  return get_image_pixel(frame.x+x,frame.y+y);
}




void
read(const char*  path)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
      png_structp  png = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
      png_infop    png_info = png_create_info_struct(png);

      png_init_io(png,f);

      png_read_info(png,png_info);

      depth = png_get_bit_depth(png,png_info);
      color_type = png_get_color_type(png,png_info);

        if(color_type != PNG_COLOR_TYPE_PALETTE)
        {
          printf("パレットでないPNGは読めません\n");

          close_read(png,png_info,f);

          throw;
        }


      auto  w = png_get_image_width( png,png_info);
      auto  h = png_get_image_height(png,png_info);

        if(w > image_size){w = image_size;}
        if(h > image_size){h = image_size;}


      png_color*  tmp_palette;

      int  color_number;

      png_get_PLTE(png,png_info,&tmp_palette,&color_number);

      palette.resize(color_number);

        for(int  i = 0;  i < color_number;  i += 1)
        {
          palette[i] = tmp_palette[i];
        }


      png_set_packing(png);

        for(int  y = 0;  y < h;  ++y)
        {
          png_read_row(png,pixels[y],nullptr);
        }


      close_read(png,png_info,f);


      reset_palette();

       cv_updater();
  ptndsp_updater();
	   }
}



void
write(const char*  path)
{
  auto  f = fopen(path,"wb");

    if(f)
    {
      png_structp  png = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);

      png_infop  png_info = png_create_info_struct(png);

      png_init_io(png,f);

      png_set_compression_level(png,Z_BEST_COMPRESSION);

      png_set_IHDR(png,png_info,image_size,image_size,4,
                   PNG_COLOR_TYPE_PALETTE,
                   PNG_INTERLACE_NONE,
                   PNG_COMPRESSION_TYPE_DEFAULT,
                   PNG_FILTER_TYPE_DEFAULT);

      png_set_PLTE(png,png_info,palette.data(),palette.size());

      png_write_info(png,png_info);

      png_set_packing(png);

        for(int  y = 0;  y < image_size;  ++y)
        {
          png_write_row(png,pixels[y]);
        }


      close_write(png,png_info,f);
	   }
}




}




