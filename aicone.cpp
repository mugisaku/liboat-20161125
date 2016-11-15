#include"libaicone/aicone_canvas.hpp"
#include"oat.hpp"
#include"sdlut.hpp"


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


/*
void
process_keyboard(const SDL_KeyboardEvent&  evt)
{
  ButtonModule*  btn = nullptr;

    switch(evt.keysym.sym)
    {
      case(SDLK_F1):
        SDL_SaveBMP(SDL_GetWindowSurface(window),"__SCREENSHOT.bmp");
        break;
      case(SDLK_LEFT ): btn = &kbd.left ;break;
      case(SDLK_RIGHT): btn = &kbd.right;break;
      case(SDLK_UP   ): btn = &kbd.up   ;break;
      case(SDLK_DOWN ): btn = &kbd.down ;break;
      case(SDLK_SPACE): btn = &kbd.space;break;

      case(SDLK_LSHIFT):
      case(SDLK_RSHIFT):
        btn = &kbd.shift;
        break;
      case(SDLK_RETURN):
      case(SDLK_z):
        btn = &kbd.advance;
        break;
      case(SDLK_RCTRL):
      case(SDLK_LCTRL):
      case(SDLK_x):
        btn = &kbd.back;
        break;
    }


    if(btn)
    {
        if(evt.state == SDL_PRESSED){btn->press()  ;}
      else                          {btn->unpress();}
    }
}
*/


IconModule
icomod = {
};


Canvas*
cv;


DirectColorImage*
img;


Dial*  r_dial;
Dial*  g_dial;
Dial*  b_dial;


RadioForm*
chkform;


void
change_color(Dial&  dial, int  old_value)
{
  int  r = r_dial->get_value();
  int  g = g_dial->get_value();
  int  b = b_dial->get_value();

  palette::index_t  i = ((1<<9)|(r<<6)|(g<<3)|b);

  img->get_color(0,0) = *palette::get_color(i);

  img->need_to_redraw();

  cv->change_color_index(i);
}


void
put(Canvas&  canvas)
{
    for(int  y = 0;  y < IconModule::size;  ++y){
    for(int  x = 0;  x < IconModule::size;  ++x){
      icomod.map[y][x] = cv->get_index(x,y);
    }}
}


void
change_using_eraser(Button&  btn)
{
	 cv->change_eraser_flag(btn.get_module().test_pressing());
}


void
change_using_grid(Button&  btn)
{
	 cv->change_grid_flag(btn.get_module().test_pressing());
}


void
reverse_h(Button&  btn)
{
    if(btn.get_module().test_unpressed())
    {
btn.need_to_reform();
    	 cv->reverse_horizontally();
    }
}


void
reverse_v(Button&  btn)
{
    if(btn.get_module().test_unpressed())
    {
    	 cv->reverse_vertically();
    }
}


void
revolve(Button&  btn)
{
    if(btn.get_module().test_unpressed())
    {
    	 cv->revolve();
    }
}


void
fn(CheckForm::Member&  member)
{
    if(member.current)
    {
      cv->change_paint_type(static_cast<Canvas::PaintType>(member.index));
    }
}


void
save(Button&  btn)
{
    if(btn.get_module().test_unpressed())
    {
      auto  f = fopen("__aicone.txt","wb");

        if(f)
        {
          icomod.print(f);

          fclose(f);
        }


      icomod.print(stdout);
    }
}


void
change_real_point(int  x, int  y)
{
  SDL_PumpEvents();

  SDL_FlushEvents(SDL_MOUSEMOTION,SDL_MOUSEBUTTONUP);
}


void
construct_widgets()
{
  master.style.background_color = const_color::gray;

  default_style.background_color = const_color::gray;
  default_style.font_color       = const_color::white;
  default_style.border_width = 1;
  default_style.border_color = const_color::red;
  default_style.left_padding   = 2;
  default_style.right_padding  = 2;
  default_style.top_padding    = 2;
  default_style.bottom_padding = 2;


  cv = new Canvas(IndexColorImageModule(IconModule::size,IconModule::size),8);

  cv->style.border_width = 2;
  cv->style.border_color = const_color::blue;

  cv->set_left_callback(put);

  cv->clear();


  auto        btn = new Button(new Text(u"save"));
  auto  erase_btn = new Button(new Text(u"消しゴム"));
  auto   grid_btn = new Button(new Text(u"グリッド"));
  auto   hrev_btn = new Button(new Text(u"水平反転"));
  auto   vrev_btn = new Button(new Text(u"垂直反転"));
  auto   rvlv_btn = new Button(new Text(u"回転"));

  erase_btn->get_module().use_toggle();
   grid_btn->get_module().use_toggle();

  btn->set_callback(save);
  erase_btn->set_callback(change_using_eraser);
   grid_btn->set_callback(change_using_grid);
   hrev_btn->set_callback(reverse_h);
   vrev_btn->set_callback(reverse_v);
   rvlv_btn->set_callback(revolve);


  r_dial = new Dial(new Text(u"R"),7);
  g_dial = new Dial(new Text(u"G"),7);
  b_dial = new Dial(new Text(u"B"),7);

  r_dial->set_callback(change_color);
  g_dial->set_callback(change_color);
  b_dial->set_callback(change_color);

  auto  rgbcol = new TableColumn({r_dial,g_dial,b_dial});

  img = new DirectColorImage(DirectColorImageModule(1,1),32);

  chkform = new RadioForm({new Text(u"点を打つ"),
                           new Text(u"線を引く"),
                           new Text(u"円を描く"),
                           new Text(u"矩形を描く"),
                           new Text(u"矩形を塗る"),
                           new Text(u"領域を塗る"),
                           });

  chkform->set_callback(fn);


  master.join(new TableColumn({cv,img,rgbcol}),32,32);
  master.join(new TableColumn({btn,erase_btn,grid_btn,hrev_btn,vrev_btn,rvlv_btn,chkform}),300,32);

    for(int  y = 0;  y < IconModule::size;  ++y){
    for(int  x = 0;  x < IconModule::size;  ++x){
      cv->get_index(x,y) = icomod.map[y][x];
    }}


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

  SDL_Init(SDL_INIT_VIDEO);

  auto&  m = oat::master.get_module();

  screen.create("An ICON Editor - " __DATE__,m.get_width(),m.get_height());

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




