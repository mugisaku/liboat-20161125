#include"oat.hpp"
#include"sdlut.hpp"
#include"pwg/pwg_device.hpp"
#include"pwg_widget/pwg_keyboard.hpp"
#include"pwg_widget/pwg_monitor.hpp"




#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace oat;
using namespace pwg;


sdlut::Screen
screen;


int
modified;


Mouse
mouse;


void
update_screen()
{
  screen.lock();

  auto&  m = master.get_module();

    for(int  y = 0;  y < m.get_height();  ++y)
    {
      auto  row = screen.get_row(y);

        for(int  x = 0;  x < m.get_width();  ++x)
        {
          auto&  pix = m.get_element(x,y);

          auto  color = screen.map_rgb(pix.r,pix.g,pix.b);

          row.put(color,x);
        }
    }


  screen.unlock();
  screen.update();
}


void
process_mouse_button(const SDL_MouseButtonEvent&  evt)
{
  mouse.change_point(Point(evt.x,evt.y));

    if(evt.button == SDL_BUTTON_LEFT)
    {
        if(evt.state == SDL_PRESSED){mouse.left.press();}
      else                          {mouse.left.unpress();}
    }

  else
    {
        if(evt.state == SDL_PRESSED){mouse.right.press();}
      else                          {mouse.right.unpress();}
    }
}


void
process_mouse_motion(const SDL_MouseMotionEvent&  evt)
{
  mouse.change_point(Point(evt.x,evt.y));


    if(evt.state&SDL_BUTTON_LMASK){mouse.left.press();}
  else                            {mouse.left.unpress();}

    if(evt.state&SDL_BUTTON_RMASK){mouse.right.press();}
  else                            {mouse.right.unpress();}
}


void
process_window(const SDL_WindowEvent&  evt)
{
    switch(evt.event)
    {
      case(SDL_WINDOWEVENT_EXPOSED):
        modified = 1;
        break;
    }
}




SDL_AudioSpec  want;
SDL_AudioSpec  have;


Keyboard*
kbd;


Monitor*
mon;


void
callback(void*  userdata, uint8_t*  stream, int  len)
{
  auto  dst     = reinterpret_cast<sample_t*>(stream);
  auto  dst_end = dst+(len/2);

    for(auto  p = dst;  p < dst_end;  ++p)
    {
      *p = have.silence;
    }


  kbd->output(dst,dst_end,mon);
}




void
construct_widgets()
{
  master.style.background_color = const_color::gray;

  default_style.background_color = const_color::gray;
  default_style.font_color       = const_color::white;
  default_style.border_width = 2;
  default_style.border_color = const_color::green;
  default_style.left_padding   = 2;
  default_style.right_padding  = 2;
  default_style.top_padding    = 2;
  default_style.bottom_padding = 2;


  kbd = new Keyboard;
  mon = new Monitor;

  master.join(new TableColumn({mon,kbd}),0,0);

  master.update();
}


void
main_loop()
{
  static SDL_Event  evt;

  int  mouse_input = 0;

    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
          case(SDL_KEYUP):
              if(!evt.key.repeat)
              {
                kbd->unpress(evt.key.keysym.sym);
              }
            break;
          case(SDL_KEYDOWN):
              if(!evt.key.repeat)
              {
                kbd->press(evt.key.keysym.sym);
              }
            break;

          case(SDL_MOUSEBUTTONUP):
          case(SDL_MOUSEBUTTONDOWN):
            mouse_input = 1;
            process_mouse_button(evt.button);
            break;
          case(SDL_MOUSEMOTION):
            mouse_input = 1;
            process_mouse_motion(evt.motion);
            break;
          case(SDL_WINDOWEVENT):
            process_window(evt.window);
            break;
          case(SDL_QUIT):
            screen.destroy();

            SDL_CloseAudio();

            SDL_Quit();
            exit(0);
            break;
        }
    }


    if(mouse_input)
    {
      master.process(mouse);

      mouse_input = 0;
    }


    if(master.update() || modified)
    {
      update_screen();

      modified = 0;
    }
}




int
main(int  argc,  char**  argv)
{
  construct_widgets();

  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

  want.freq = sample_rate;
  want.format = AUDIO_S16SYS;
  want.channels = 1;
  want.samples = 1024;
  want.callback = callback;

  SDL_OpenAudio(&want,&have);

  Device::change_silence(have.silence);


  auto&  m = oat::master.get_module();

  screen.create("EDitor for SouND - " __DATE__,m.get_width(),m.get_height());

  update_screen();

  SDL_PauseAudio(0);

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,-1,false);
#else
    for(;;)
    {
      main_loop();

      SDL_Delay(20);
    }
#endif


  return 0;
}




