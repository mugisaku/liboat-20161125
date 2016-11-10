#include"oat.hpp"
#include"sdlut.hpp"
#include"pngio.cpp"


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




pngio::Object
png;


constexpr int  moment_width  = 24;
constexpr int  moment_height = 32;
constexpr int  motion_number = 3;
constexpr int  color_number = 8;


const Color
palette[color_number] =
{
  Color(0x1F),
  Color(0x3F),
  Color(0x5F),
  Color(0x7F),
  Color(0x9F),
  Color(0xBF),
  Color(0xDF),
  Color(0xFF),
};


int
color_index;


int  x_base;
int  y_base;


class
ColorSelector: public Widget
{
static constexpr int   frame_size = 20;
static constexpr int  square_size = 16;


public:
ColorSelector()
{
  change_content_width( frame_size*color_number/2);
  change_content_height(frame_size*2);
}


void
process_mouse(const Mouse&  mouse) override
{
  auto  pt = get_mouse_point(mouse);

    if(mouse.left.test_pressing())
    {
      color_index = (pt.x/frame_size)<<1;
      color_index |= (pt.y < frame_size)?0:1;

      need_to_redraw();
    }
}


void
render() override
{
  fill();


  auto  pt = content.point;

  const Color*  color = ::palette;

    for(int  x = 0;  x < color_number/2;  ++x)
    {
      fill_rect(*color++,pt.x+(frame_size*x),pt.y,square_size,square_size);
      fill_rect(*color++,pt.x+(frame_size*x),pt.y+frame_size,square_size,square_size);
    }


  draw_rect(const_color::white,pt.x+(frame_size*(color_index>>1)),
                               pt.y+(color_index&1? frame_size:0),frame_size,frame_size);
}
};




class
Display: public Widget
{
static constexpr int  pixel_size = 2;

int  phase;

uint32_t  last_time;

public:
Display()
{
  last_time = 0;

  phase = 0;

  change_content_width( moment_width *pixel_size);
  change_content_height(moment_height*pixel_size);
}


void
check()
{
  auto  now = SDL_GetTicks();

    if(now >= last_time+200)
    {
      last_time = now;

      ++phase;

      need_to_redraw();
    }
}


void
render() override
{
  fill();

  auto  pt = content.point;

  static const int  base[] = {0,moment_width,0,moment_width*2};

    for(int  y = 0;  y < moment_height;  y += 1){
    for(int  x = 0;  x < moment_width ;  x += 1){
      auto  v = png.get_pixel(base[phase&3]+x,y_base+y);

        if(v&8)
        {
          fill_rect(::palette[v&7],pt.x+(pixel_size*x),
                                   pt.y+(pixel_size*y),pixel_size,pixel_size);
        }
    }}
}
};


Display*
dsp;


RadioForm*
radfrm;


int
tool_index;


class
Canvas: public Widget
{
static constexpr int  pixel_size = 10;

const int  x_base;

bool  table[moment_height][moment_width];


public:
Canvas(int  base):
x_base(base)
{
  change_content_width( moment_width *pixel_size);
  change_content_height(moment_height*pixel_size);
}


void
search(int  x, int  y, uint8_t  target)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

      auto&  pixel = png.get_pixel(x_base+x,y_base+y);

        if(pixel == target)
        {
          pixel = (color_index|8);

            if(x                    ){search(x-1,y  ,target);}
            if(y                    ){search(x  ,y-1,target);}
            if(x < (moment_width -1)){search(x+1,y  ,target);}
            if(y < (moment_height-1)){search(x  ,y+1,target);}
        }
    }
}


void
process_mouse(const Mouse&  mouse) override
{
  auto  pt = get_mouse_point(mouse);

  int  x = pt.x/pixel_size;
  int  y = pt.y/pixel_size;

    switch(tool_index)
    {
  case(0):
        if(mouse.left.test_pressing())
        {
          png.get_pixel(x_base+x,y_base+y) = color_index|8;

          dsp->need_to_redraw();

          need_to_redraw();
        }

      else
        if(mouse.right.test_pressing())
        {
          png.get_pixel(x_base+x,y_base+y) = 0;

          dsp->need_to_redraw();

          need_to_redraw();
        }
      break;
  case(1):
        if(mouse.left.test_pressing())
        {
          auto  target = png.get_pixel(x_base+x,y_base+y);

            if(target != (color_index|8))
            {
              std::memset(&table,0,sizeof(table));

              search(x,y,target);

              dsp->need_to_redraw();

              need_to_redraw();
            }
        }
      break;
    }
}


void
render() override
{
  fill();


  auto  pt = content.point;

  constexpr Color  l1(0x7F,0x7F,0x0);
  constexpr Color  l2(0xFF,0xFF,0x00);

    for(int  y = 0;  y < moment_height;  y += 1)
    {
        for(int  x = 0;  x < moment_width;  x += 1)
        {
          auto  v = png.get_pixel(x_base+x,y_base+y);

            if(v&8)
            {
              fill_rect(::palette[v&7],pt.x+(pixel_size*x),
                                       pt.y+(pixel_size*y),pixel_size,pixel_size);
            }


          draw_vline(l1,pt.x+pixel_size*x,
                        pt.y,
                        pixel_size*moment_height);
        }


      draw_hline(l1,pt.x,
                    pt.y+pixel_size*y,
                    pixel_size*moment_width);
    }


  draw_hline(l2,pt.x,
                pt.y+pixel_size*16+1,
                pixel_size*moment_width);

  draw_vline(l2,pt.x+pixel_size*12+1,
                pt.y,
                pixel_size*moment_height);
}



};


Widget*  cv_array[motion_number];


Dial*
dial;


void
save(Button&  btn)
{
    if(btn->test_unpressed())
    {
      static int  n;

      char  buf[256];

      snprintf(buf,sizeof(buf),"__PTRN%03d.png",n++);

      png.write(buf);
    }
}


void
change_tool(RadioForm::Member&  m)
{
    if(m.current)
    {
      tool_index = m.index;
    }
}


void
append_new(Button&  btn)
{
    if(btn->test_unpressed())
    {
      png.resize(moment_width*motion_number,png.height+moment_height);

      dial->reset(png.height/moment_height,1,1);
    }
}


void
change(Dial&  d, int  old_value)
{
  y_base = moment_height*(d.get_value()-1);

  dsp->need_to_redraw();

    for(auto  cv: cv_array)
    {
      cv->need_to_redraw();
    }
}


void
reset_palette()
{
  png.palette.resize(color_number*2);

  png.set_palette_gray( 0,0x1F);
  png.set_palette_gray( 1,0x3F);
  png.set_palette_gray( 2,0x5F);
  png.set_palette_gray( 3,0x7F);
  png.set_palette_gray( 4,0x9F);
  png.set_palette_gray( 5,0xBF);
  png.set_palette_gray( 6,0xDF);
  png.set_palette_gray( 7,0xFF);
  png.set_palette_gray( 8,0x1F);
  png.set_palette_gray( 9,0x3F);
  png.set_palette_gray(10,0x5F);
  png.set_palette_gray(11,0x7F);
  png.set_palette_gray(12,0x9F);
  png.set_palette_gray(13,0xBF);
  png.set_palette_gray(14,0xDF);
  png.set_palette_gray(15,0xFF);
}


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


  png.resize(moment_width*motion_number,moment_height);

  reset_palette();

  dsp = new Display;


  dsp->style.background_color = const_color::blue;

  int  x_base = 0;

    for(auto&  cv: cv_array)
    {
      cv = new ::Canvas(x_base);

      x_base += moment_width;

      cv->style.background_color = const_color::blue;
      cv->style.border_width = 4;
    }


  dial = new Dial(nullptr,1,1,1);

  dial->set_callback(change);

  auto  colsel = new ColorSelector;

  auto  save_btn = new Button(new Text(u"PNGで保存"));
  auto  appn_btn = new Button(new Text(u"新規追加"));

  radfrm = new RadioForm({new Text(u"点を打つ"),new Text(u"領域を塗りつぶす")});

  radfrm->set_callback(change_tool);

  save_btn->set_callback(save);
  appn_btn->set_callback(append_new);

  auto  fntbl = new TableRow({dial,appn_btn,save_btn});

  auto  cvtbl = new TableRow({cv_array[0],cv_array[1],cv_array[2]});

  master.join(new TableColumn({new TableRow({colsel,dsp,radfrm,fntbl}),
                               cvtbl,
                              }),0,0);

  master.update();
}


void
load(char*  path)
{
  png.read(path);

  reset_palette();

  y_base = 0;

  dial->reset(png.height/moment_height,1,1);

  dsp->need_to_redraw();

    for(auto  cv: cv_array)
    {
      cv->need_to_redraw();
    }


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

      mouse_input = 0;
    }


  dsp->check();

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

  screen.create("mkptrn - " __DATE__,m.get_width(),m.get_height());

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




