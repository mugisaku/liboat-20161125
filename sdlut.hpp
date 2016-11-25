#ifndef SDL__UT_HPP_
#define SDL__UT_HPP_


#include<cstdint>

#ifdef EMSCRIPTEN
#include<SDL/SDL.h>
#else
#include<SDL2/SDL.h>
#endif


namespace sdlut{


class
SurfaceRow
{
  uint8_t*  ptr;
  const int  bpp;

public:
  SurfaceRow(uint8_t*  p, int  b):
  ptr(p),
  bpp(b){}


  uint32_t  get(int  x=0) const
  {
    auto  p = ptr+bpp*x;

      switch(bpp)
      {
        case(1): return *reinterpret_cast<const uint8_t*>( p);
        case(2): return *reinterpret_cast<const uint16_t*>(p);
        case(4): return *reinterpret_cast<const uint32_t*>(p);
      }


    return  0;
  }

  void  put(uint32_t  color, int  x=0)
  {
    auto  p = ptr+bpp*x;

      switch(bpp)
      {
        case(1): *reinterpret_cast<uint8_t*>( p) = color;break;
        case(2): *reinterpret_cast<uint16_t*>(p) = color;break;
        case(4): *reinterpret_cast<uint32_t*>(p) = color;break;
      }
  }

};


class
Surface
{
protected:
  SDL_Surface*  sdldata;

  int  bpp;

public:
  Surface(SDL_Surface*  data=nullptr):
  bpp(0)
  {
    reset(data);
  }



  int  get_width()  const{return sdldata->w;}
  int  get_height() const{return sdldata->h;}
  int  get_pitch()  const{return sdldata->pitch;}
  int  get_bpp()  const{return bpp;}

  SDL_Surface*  operator->() const{return sdldata;}

  void  free()
  {
    SDL_FreeSurface(sdldata);
  }


  void  reset(SDL_Surface*  data)
  {
      if(data)
      {
        sdldata = data;

        bpp = data->format->BytesPerPixel;
      }
  }


  SurfaceRow  get_row(int  y) const
  {
    auto  ptr = static_cast<uint8_t*>(sdldata->pixels);

    return SurfaceRow(ptr+(sdldata->pitch*y),bpp);
  }


  uint32_t  map_rgb(uint8_t  r, uint8_t  g, uint8_t  b) const
  {
    return SDL_MapRGB(sdldata->format,r,g,b);
  }

  void  draw_rect(uint32_t  color, int  x, int  y, int  w, int  h)
  {
      for(int  yy = 0;  yy < h;  ++yy)
      {
        get_row(y+yy).put(color,x    );
        get_row(y+yy).put(color,x+w-1);
      }


    auto     top = get_row(y    );
    auto  bottom = get_row(y+h-1);

      for(int  xx = 0;  xx < w;  ++xx)
      {
           top.put(color,x+xx);
        bottom.put(color,x+xx);
      }
  }

  void  fill_rect(uint32_t  color, int  x, int  y, int  w, int  h)
  {
    SDL_Rect  rect = {x,y,w,h};

    SDL_FillRect(sdldata,&rect,color);
  }

  void  save(const char*  path){SDL_SaveBMP(sdldata,path);}
  
  void  fill(){SDL_FillRect(sdldata,nullptr,0);}

};


class
Screen: public Surface
{
  SDL_Window*  window;

public:
  Screen(): window(nullptr){}

  void  create(const char*  title, int  w, int  h)
  {
    destroy();

    window = SDL_CreateWindow(title,32,32,w,h,0);

    Surface::reset(SDL_GetWindowSurface(window));
  }

  void  destroy()
  {
    SDL_DestroyWindow(window);
  }

  void  change_title(const char*  s)
  {
    SDL_SetWindowTitle(window,s);
  }

  void  change_fullscreen()
  {
  }


  void    lock(){SDL_LockSurface(  sdldata);}
  void  unlock(){SDL_UnlockSurface(sdldata);}

  void  update() const{SDL_UpdateWindowSurface(window);}
  
};


}


#endif




