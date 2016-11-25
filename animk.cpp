#include"oat.hpp"
#include"sdlut.hpp"
#include"libmg/mg_core.hpp"
#include"libmg/mg_colorselector.hpp"
#include"libmg/mg_motionselector.hpp"
#include"libmg/mg_animationdisplay.hpp"
#include"libmg/mg_framepositioner.hpp"
#include"libmg/mg_canvas.hpp"
#include"libmg/mg_widget.hpp"


#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace oat;


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




Canvas*          canvas;
ColorSelector*   colsel;
MotionSelector*  motsel;
AnimationDisplay*   dsp;


void
construct_widgets()
{
  master.style.background_color = const_color::gray;

  default_style.background_color = const_color::dark_gray;
  default_style.font_color       = const_color::white;
  default_style.border_width = 1;
  default_style.border_color = const_color::white;
  default_style.left_padding   = 2;
  default_style.right_padding  = 2;
  default_style.top_padding    = 2;
  default_style.bottom_padding = 2;


  core::set_parameter(24,40,3);

  canvas = new Canvas(true);
     dsp = new AnimationDisplay;
  colsel = new ColorSelector;
  motsel = new MotionSelector;

  auto  anitbl = new TableColumn({motsel,dsp});

  master.join(new TableColumn({new TableRow({canvas,anitbl,new FramePositioner}),
                               new TableRow({colsel,create_tool_widget(),create_edit_widget(),create_manager_widget()}),
                              }),0,0);

  master.update();
}


const char*
get_title()
{
  static char  buf[256];

  snprintf(buf,sizeof(buf),"%s - animk " __DATE__,core::get_filepath());

  return buf;
}


void
load(char*  path)
{
  core::read(path);

  screen.change_title(get_title());

  SDL_free(path);
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
          case(SDL_DROPFILE):
            load(evt.drop.file);
            break;
          case(SDL_QUIT):
            screen.destroy();
            SDL_Quit();
            exit(0);
            break;
        }
    }


    if(mouse_input)
    {
      master.process(mouse);

      auto  v = core::get_modified_flags();

        if(v&core::canvas_modified_flag){canvas->need_to_redraw();}
        if(v&core::colorselector_modified_flag){colsel->need_to_redraw();}
        if(v&core::animationdisplay_modified_flag){dsp->need_to_redraw();}


      mouse_input = 0;
    }


  auto  now = SDL_GetTicks();

  dsp->check(now);

  static uint32_t  next_time;

    if(now >= next_time)
    {
      next_time = now+120;

        if(master.update() || modified)
        {
          update_screen();

          modified = 0;
        }
    }
}


int
main(int  argc,  char**  argv)
{
  construct_widgets();

  SDL_Init(SDL_INIT_VIDEO);

  auto&  m = oat::master.get_module();

  screen.create(get_title(),m.get_width(),m.get_height());

  update_screen();

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




