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


constexpr int  base_size = 16;
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


int
base_index;


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
public:
Display()
{
  change_content_width( base_size*pixel_size*4);
  change_content_height(base_size*pixel_size*4);
}


void
render() override
{
  fill();

  auto  pt = content.point;

    for(int  y = 0;  y < 4;  y += 1){
    for(int  x = 0;  x < 4;  x += 1){
    for(int  yy = 0;  yy < base_size;  yy += 1){
    for(int  xx = 0;  xx < base_size;  xx += 1){
      auto  v = png.get_pixel(xx,base_index+yy);

        if(v&8)
        {
          fill_rect(::palette[v&7],pt.x+(base_size*pixel_size*x)+(pixel_size*xx),
                                   pt.y+(base_size*pixel_size*y)+(pixel_size*yy),pixel_size,pixel_size);
        }
    }}}}
}
};


Widget*
dsp;


RadioForm*
radfrm;


int
tool_index;


class
Base: public Widget
{
static constexpr int  pixel_size = 10;

bool  table[base_size][base_size];


public:
Base()
{
  change_content_width( base_size*pixel_size);
  change_content_height(base_size*pixel_size);
}


void
search(int  x, int  y, uint8_t  target)
{
  auto&  e = table[y][x];

    if(!e)
    {
      e = true;

      auto&  pixel = png.get_pixel(x,base_index+y);

        if(pixel == target)
        {
          pixel = (color_index|8);

            if(x                ){search(x-1,y  ,target);}
            if(y                ){search(x  ,y-1,target);}
            if(x < (base_size-1)){search(x+1,y  ,target);}
            if(y < (base_size-1)){search(x  ,y+1,target);}
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
          png.get_pixel(x,base_index+y) = color_index|8;

          dsp->need_to_redraw();

          need_to_redraw();
        }

      else
        if(mouse.right.test_pressing())
        {
          png.get_pixel(x,base_index+y) = 0;

          dsp->need_to_redraw();

          need_to_redraw();
        }
      break;
  case(1):
        if(mouse.left.test_pressing())
        {
          auto  target = png.get_pixel(x,base_index+y);

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

    for(int  y = 0;  y < base_size;  y += 1)
    {
      draw_hline(const_color::yellow,pt.x,
                                     pt.y+pixel_size*y,
                                     pixel_size*base_size);

        for(int  x = 0;  x < base_size;  x += 1)
        {
          draw_vline(const_color::yellow,pt.x+pixel_size*x,
                                         pt.y,
                                         pixel_size*base_size);

          auto  v = png.get_pixel(x,base_index+y);

            if(v&8)
            {
              fill_rect(::palette[v&7],pt.x+(pixel_size*x),
                                       pt.y+(pixel_size*y),pixel_size,pixel_size);
            }
        }
    }
}



};


Widget*
bas;


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
fill(Button&  btn)
{
    if(btn->test_unpressed())
    {
        for(int  y = 0;  y < base_size;  y += 1){
        for(int  x = 0;  x < base_size;  x += 1){
          png.get_pixel(x,base_index+y) = 8|color_index;
        }}


      dsp->need_to_redraw();
      bas->need_to_redraw();
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
      png.resize(base_size,png.height+base_size);

      dial->reset(png.height/base_size,1,1);
    }
}


void
change(Dial&  d, int  old_value)
{
  base_index = base_size*(d.get_value()-1);

  dsp->need_to_redraw();
  bas->need_to_redraw();
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


  png.resize(base_size,base_size);

  reset_palette();

  dsp = new Display;
  bas = new Base;

  dsp->style.background_color = const_color::blue;
  bas->style.background_color = const_color::blue;

  dial = new Dial(nullptr,1,1,1);

  dial->set_callback(change);

  auto  colsel = new ColorSelector;

  auto  save_btn = new Button(new Text(u"PNGで保存"));
  auto  appn_btn = new Button(new Text(u"新規追加"));

  radfrm = new RadioForm({new Text(u"点を打つ"),new Text(u"領域を塗りつぶす")});

  radfrm->set_callback(change_tool);

  auto  fill_btn = new Button(new Text(u"　全塗りつぶし"));

  save_btn->set_callback(save);
  appn_btn->set_callback(append_new);
  fill_btn->set_callback(fill);

  master.join(new TableColumn({colsel,
                               new TableRow({bas,dsp}),
                               new TableRow({radfrm,fill_btn}),
                               new TableRow({dial,appn_btn}),
                               save_btn}),0,0);

  master.update();
}


void
load(char*  path)
{
  png.read(path);

  reset_palette();

  base_index = 0;

  dial->reset(png.height/base_size,1,1);

  bas->need_to_redraw();
  dsp->need_to_redraw();

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




