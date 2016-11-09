#include<cstdint>
#include<cstring>
#include<cstdio>
#include<vector>
#include<libpng/png.h>
#include<zlib.h>




namespace pngio{


struct
Object
{
  int  width;
  int  height;

  int  color_type;

  int  depth;

  std::vector<png_color>  palette;

  std::vector<uint8_t>  pixels;

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


uint8_t&
get_pixel(int  x, int  y)
{
  return pixels[(width*y)+x];
}


void
resize(int  w, int  h)
{
  width  = w;
  height = h;

  pixels.resize(width*height);
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


      resize(png_get_image_width( png,png_info),
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

        for(int  y = 0;  y < height;  ++y)
        {
          png_read_row(png,&pixels[width*y],nullptr);
        }


      close_read(png,png_info,f);
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

      png_set_IHDR(png,png_info,width,height,4,
                   PNG_COLOR_TYPE_PALETTE,
                   PNG_INTERLACE_NONE,
                   PNG_COMPRESSION_TYPE_DEFAULT,
                   PNG_FILTER_TYPE_DEFAULT);

      png_set_PLTE(png,png_info,palette.data(),palette.size());

      png_write_info(png,png_info);

      png_set_packing(png);

        for(int  y = 0;  y < height;  ++y)
        {
          png_write_row(png,&pixels[width*y]);
        }


      close_write(png,png_info,f);
	   }
}


};


}




