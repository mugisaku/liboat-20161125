#include"fcfont.hpp"
#include<SDL.h>




void
print(const uint8_t*  p, SDL_Surface*  bmp, int  x_base, int  y_base)
{
    for(int  y = 0;  y < 8;  ++y)
    {
      auto  src = *p++;

      auto  dst = (uint32_t*)(static_cast<uint8_t*>(bmp->pixels)+(bmp->pitch*(y_base+y)));

        for(int  x = 0;  x < 8;  ++x)
        {
            if(src&0x80)
            {
              dst[x_base+x] = 0xFFFFFFFF;
            }


          src <<= 1;
        }
    }
}


int
main(int  argc, char**  argv)
{
  SDL_Init(0);

  auto  bmp = SDL_CreateRGBSurface(0,320,640,32,0xFF0000,0xFF00,0xFF,0);

  fcfont::Character::reset_table();

    for(int  y = 0;  y <= 0xFF;  ++y)
    {
        for(int  x = 0;  x <= 0xF;  ++x)
        {
          uint16_t  unicode = 0x3000|(y<<4)|x;

          auto  c = fcfont::Character::pointer_table[unicode];

            if(c)
            {
              print(c->data,bmp,8*x,8*y);
            }
        }
    }


    for(int  y = 0;  y <= 0x7;  ++y)
    {
        for(int  x = 0;  x <= 0xF;  ++x)
        {
          uint16_t  unicode = (y<<4)|x;

          auto  c = fcfont::Character::pointer_table[unicode];

            if(c)
            {
              print(c->data,bmp,8*x,320+8*y);
            }
        }
    }


  SDL_SaveBMP(bmp,"save.bmp");

  SDL_FreeSurface(bmp);

  SDL_Quit();

  return 0;
}




