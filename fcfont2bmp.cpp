#include"fcfont.hpp"
#include<SDL.h>




size_t
get_utf8_byte_number(const char*  s)
{
  const int  c = *(const unsigned char*)s;

       if(!(c>>7)             ){return 1;}
/*
  else if( (c>>1) == 0b1111110){return 6;}
  else if( (c>>2) == 0b111110 ){return 5;}
  else if( (c>>3) == 0b11110  ){return 4;}
*/
  else if( (c>>4) == 0b1110   ){return 3;}
  else if( (c>>5) == 0b110    ){return 2;}
  else if( (c>>6) == 0b10     ){return 1;}


  return 0;
}


size_t
get_unicode_length(const char*  s)
{
  size_t  length = 0;

    for(;;)
    {
      const size_t  byte_number = get_utf8_byte_number(s);

        if(!byte_number)
        {
          break;
        }


      ++length;

      s += byte_number;
    }


  return length;
}


char16_t
to_char16(const char*  s, size_t  byte_number)
{
    switch(byte_number)
    {
      case(1): return ((s[0]             )                                    );break;
      case(2): return ((s[0]&0b11111)<< 6)|((s[1]&0b111111)                   );break;
      case(3): return ((s[0]&0b01111)<<12)|((s[1]&0b111111)<<6)|(s[2]&0b111111);break;
    }


  return 0;
}


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


void
print(const char*  s, SDL_Surface*  bmp)
{
  int  x = 0;
  int  y = 0;

    while(*s)
    {
        if(((x+ 8) >= bmp->w) ||
           ((y+16) >= bmp->h))
        {
          break;
        }


      auto  n = get_utf8_byte_number(s);

      auto  c = to_char16(s,n);

      s += n;

        if(c == '\n')
        {
          x  =  0;
          y += 16;

          continue;
        }


      auto  cmb = fcfont::Combined::pointer_table[c];

        if(cmb)
        {
          auto&  upper = *fcfont::Character::pointer_table[cmb->upper];
          auto&  lower = *fcfont::Character::pointer_table[cmb->lower];

          print(upper.data,bmp,x,y  );
          print(lower.data,bmp,x,y+8);

          x += 8;
        }
    }
}


void
load(const char*  path, std::string&  buf)
{
  auto  f = fopen(path,"rb");

    if(f)
    {
        for(;;)
        {
          auto  c = fgetc(f);

            if(feof(f))
            {
              break;
            }


          buf.push_back(c);
        }


      fclose(f);
    }
}


int
main(int  argc, char**  argv)
{
  --argc;
  ++argv;

  std::string  s;

    while(argc--)
    {
      load(*argv++,s);
    }


  SDL_Init(0);

  auto  bmp = SDL_CreateRGBSurface(0,320,320,32,0xFF0000,0xFF00,0xFF,0);

  fcfont::Character::reset_table();
  fcfont::Combined::reset_table();

  print(s.data(),bmp);


  SDL_SaveBMP(bmp,"save.bmp");

  SDL_FreeSurface(bmp);

  SDL_Quit();

  return 0;
}




