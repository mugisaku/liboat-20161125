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
oat::WidgetUpdater    dial_updater;


int  image_width;
int  image_height;

int  chip_width;
int  chip_height;

int  chip_number;

int  color_index;

int  color_type;

int  depth;

std::vector<png_color>  palette;

int  tool_index;


std::vector<uint8_t>  pixels;


int  x_offset;
int  y_offset;







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
resize_image(int  w, int  h)
{
  image_width  = w;
  image_height = h;

  pixels.resize(w*h);
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

  x_offset = 0;
  y_offset = 0;

  reset_palette();

  resize_image(chip_width*chip_number,chip_height);
}


void  set_canvas_updater(oat::WidgetUpdater  upd){cv_updater = upd;}
void  set_colorselector_updater(oat::WidgetUpdater  upd){colsel_updater = upd;}
void  set_patterndisplay_updater(oat::WidgetUpdater  upd){ptndsp_updater = upd;}
void  set_animationdisplay_updater(oat::WidgetUpdater  upd){anidsp_updater = upd;}
void  set_dial_updater(oat::WidgetUpdater  upd){dial_updater = upd;}




int  get_image_width(){return image_width;}
int  get_image_height(){return image_height;}

int  get_chip_width(){return chip_width;}
int  get_chip_height(){return chip_height;}
int  get_chip_number(){return chip_number;}




namespace{
int
clamp(int  v, int  max, int  min)
{
  return((v <= min)?   0:
         (v >= max)? max:v);
}
}


void
move_x_offset(int  v)
{
  x_offset = clamp(chip_width*v,image_width-chip_width,0);

   cv_updater();
  ptndsp_updater();
}


void
move_y_offset(int  v)
{
  y_offset = clamp(chip_height*v,image_height-chip_height,0);

   cv_updater();
  ptndsp_updater();
}


int
get_x_offset()
{
  return x_offset;
}


int
get_y_offset()
{
  return y_offset;
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




int
extend()
{
  image_height += chip_height;

  pixels.resize(image_width*image_height);


  return (image_height/chip_height);
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
  pixels[(image_width*(y_offset+y))+x_offset+x] = color_index_;

   cv_updater();
  ptndsp_updater();
}


int
get_image_pixel(int  x, int  y)
{
  return pixels[(image_width*y)+x];
}


int
get_chip_pixel(int  x, int  y)
{
  return get_image_pixel(x_offset+x,y_offset+y);
}


int
get_segment_pixel(int  x, int  y)
{
  return get_image_pixel(x,y_offset+y);
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


      resize_image(png_get_image_width( png,png_info),
                   png_get_image_height(png,png_info));

      png_color*  tmp_palette;

      int  color_number;

      png_get_PLTE(png,png_info,&tmp_palette,&color_number);

      palette.resize(color_number);

        for(int  i = 0;  i < color_number;  i += 1)
        {
          palette[i] = tmp_palette[i];
        }


      png_set_packing(png);

        for(int  y = 0;  y < image_height;  ++y)
        {
          png_read_row(png,&pixels[image_width*y],nullptr);
        }


      close_read(png,png_info,f);


      reset_palette();

       cv_updater();
  ptndsp_updater();
      dial_updater();
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

      png_set_IHDR(png,png_info,image_width,image_height,4,
                   PNG_COLOR_TYPE_PALETTE,
                   PNG_INTERLACE_NONE,
                   PNG_COMPRESSION_TYPE_DEFAULT,
                   PNG_FILTER_TYPE_DEFAULT);

      png_set_PLTE(png,png_info,palette.data(),palette.size());

      png_write_info(png,png_info);

      png_set_packing(png);

        for(int  y = 0;  y < image_height;  ++y)
        {
          png_write_row(png,&pixels[image_width*y]);
        }


      close_write(png,png_info,f);
	   }
}




}




