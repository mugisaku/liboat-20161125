#include"oat.hpp"
#include"sdlut.hpp"
#include"space.hpp"
#include<cstdlib>

#ifdef EMSCRIPTEN
#include<emscripten.h>
#endif


using namespace oat;


int
modified;


Mouse
mouse;


sdlut::Screen
screen;


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


Text*
txt;


class
Device: public Widget
{
public:
  Bitmap  bitmap;

  SpaceManager  spman;

  Point   first_point;
  Point  cursor_point;

  Device(int  w, int  h): bitmap(w,h)
  {
    change_content_width( w);
    change_content_height(h);

    first_point.x = -1;
  }


  void  make_spaces()
  {
    spman.convert(bitmap);

    char  buf[8];

    snprintf(buf,sizeof(buf),"%3d",spman.spaces.size());

    txt->change_string(buf);
/*
    spman.link();

    spman.make_group();
printf("spaces %4d\n",spman.spaces.size());
printf("groups %4d\n",spman.groups.size());
*/
    need_to_redraw();
  }

  void  clear()
  {
    bitmap.clear();

    spman.clear();

    txt->change_string("  0");

    need_to_redraw();
  }

  void  process_mouse(const Mouse&  mouse) override
  {
    auto  pt = get_mouse_point(mouse);

      if(mouse.left.test_pressing())
      {
          if(first_point.x < 0)
          {
            first_point = pt;
          }


        cursor_point = pt;

        need_to_redraw();
      }

    else
      if(mouse.left.test_unpressed())
      {
        Rectangle  rect(first_point,pt);

          for(int  y = 0;  y < rect.height;  ++y){
          for(int  x = 0;  x < rect.width ;  ++x){
            bitmap.get(rect.point.x+x,rect.point.y+y) = 1;
          }}


        bitmap.frame();

        first_point.x = -1;

        need_to_redraw();
      }
  }

  void  render_space(const Space&  sp)
  {
    const auto&  pt = content.point;

      for(int  y = sp.top ;  y <= sp.bottom-sp.liquid_level;  ++y){
      for(int  x = sp.left;  x <= sp.right                 ;  ++x){
        draw_dot(const_color::white,pt.x+x,pt.y+y);
      }}


      for(int  y = sp.bottom-sp.liquid_level;  y <= sp.bottom;  ++y){
      for(int  x = sp.left                  ;  x <= sp.right ;  ++x){
//        draw_dot(const_color::blue,pt.x+x,pt.y+y);
      }}
  }

  void  render() override
  {
    fill();

    const auto&  pt = content.point;

/*      if(spman.spaces.size())
      {
          for(auto&  sp: spman.spaces)
          {
//            render_space(sp);
          }
      }

    else
*/
      {
          for(int  y = 0;  y < bitmap.height;  ++y){
          for(int  x = 0;  x < bitmap.width ;  ++x){
            auto  c = bitmap.get(x,y);
            auto&  color = (c == 0)? const_color::black:
                           (c == 1)? const_color::white:
                                     const_color::red  ;

            draw_dot(color,pt.x+x,pt.y+y);
          }}
      }


      if(first_point.x >= 0)
      {
        Rectangle  rect(first_point,cursor_point);

        draw_rect(const_color::red,pt.x+rect.point.x,
                                   pt.y+rect.point.y,
                                   rect.width,
                                   rect.height);
      }
  }

};


Device*
dev;


void
call_correct(Button&  btn)
{
    if(btn.get_module().test_pressed())
    {
      dev->make_spaces();
    }
}


void
call_clear(Button&  btn)
{
    if(btn.get_module().test_pressed())
    {
      dev->clear();
    }
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


  dev = new Device(320,320);
  txt = new Text(u"  0");

  auto  cor_btn = new Button(new Text(u"回収"));
  auto  clr_btn = new Button(new Text(u"消去"));

  cor_btn->set_callback(call_correct);
  clr_btn->set_callback(call_clear);

  auto  row = new TableRow({cor_btn,clr_btn,txt});

  master.join(new TableColumn({row,dev}),0,0);

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
          case(SDL_QUIT):
            screen.destroy();
            SDL_Quit();
            exit(0);
            break;
          default:;
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

  screen.create("correct",m.get_width(),m.get_height());

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




