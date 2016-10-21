#include"pwg_keyboard.hpp"
#include"pwg_monitor.hpp"
#include<mutex>




namespace pwg{




Keyboard::
Keyboard():
sine_keyrow(*this,WaveKind::sine),
square_keyrow(*this,WaveKind::square),
triangle_keyrow(*this,WaveKind::triangle),
sawtooth_keyrow(*this,WaveKind::sawtooth),
noise(8000)
{
  join(new oat::TableColumn({    sine_keyrow.create_table(u"正弦波"),
                               square_keyrow.create_table(u"矩形波"),
                             triangle_keyrow.create_table(u"三角波"),
                             sawtooth_keyrow.create_table(u"鋸歯波")}),0,0);
}




Key*
Keyboard::
get_key(SDL_Keycode  kode)
{
  Key*  k = nullptr;

    switch(kode)
    {
  case(SDLK_9): k = sine_keyrow.get_key(7);break;
  case(SDLK_8): k = sine_keyrow.get_key(6);break;
  case(SDLK_7): k = sine_keyrow.get_key(5);break;
  case(SDLK_6): k = sine_keyrow.get_key(4);break;
  case(SDLK_5): k = sine_keyrow.get_key(3);break;
  case(SDLK_4): k = sine_keyrow.get_key(2);break;
  case(SDLK_3): k = sine_keyrow.get_key(1);break;
  case(SDLK_2): k = sine_keyrow.get_key(0);break;

  case(SDLK_o): k = square_keyrow.get_key(7);break;
  case(SDLK_i): k = square_keyrow.get_key(6);break;
  case(SDLK_u): k = square_keyrow.get_key(5);break;
  case(SDLK_y): k = square_keyrow.get_key(4);break;
  case(SDLK_t): k = square_keyrow.get_key(3);break;
  case(SDLK_r): k = square_keyrow.get_key(2);break;
  case(SDLK_e): k = square_keyrow.get_key(1);break;
  case(SDLK_w): k = square_keyrow.get_key(0);break;

  case(SDLK_l): k = triangle_keyrow.get_key(7);break;
  case(SDLK_k): k = triangle_keyrow.get_key(6);break;
  case(SDLK_j): k = triangle_keyrow.get_key(5);break;
  case(SDLK_h): k = triangle_keyrow.get_key(4);break;
  case(SDLK_g): k = triangle_keyrow.get_key(3);break;
  case(SDLK_f): k = triangle_keyrow.get_key(2);break;
  case(SDLK_d): k = triangle_keyrow.get_key(1);break;
  case(SDLK_s): k = triangle_keyrow.get_key(0);break;

  case(SDLK_COMMA): k = sawtooth_keyrow.get_key(7);break;
  case(SDLK_m    ): k = sawtooth_keyrow.get_key(6);break;
  case(SDLK_n    ): k = sawtooth_keyrow.get_key(5);break;
  case(SDLK_b    ): k = sawtooth_keyrow.get_key(4);break;
  case(SDLK_v    ): k = sawtooth_keyrow.get_key(3);break;
  case(SDLK_c    ): k = sawtooth_keyrow.get_key(2);break;
  case(SDLK_x    ): k = sawtooth_keyrow.get_key(1);break;
  case(SDLK_z    ): k = sawtooth_keyrow.get_key(0);break;
    }


  return k;
}


void
Keyboard::
push(Key*  k)
{
    if(k)
    {
      active_key_list.emplace_back(k);
    }
}


void
Keyboard::
press(SDL_Keycode  kode)
{
  auto  k = get_key(kode);

    if(k)
    {
      k->button->press();
    }

  else
    {
      noise.reset_play_counter(sample_rate*20);
      noise.start();
      noise.unmute();
    }
}


void
Keyboard::
unpress(SDL_Keycode  kode)
{
  auto  k = get_key(kode);

    if(k)
    {
      k->button->unpress();
    }

  else
    {
      noise.mute();
      noise.stop();
    }
}


void
Keyboard::
output(sample_t*  dst, const sample_t*  dst_end, Monitor*  mon)
{
    if(mon)
    {
      mon->clear();
    }


    while(dst < dst_end)
    {
      int  v = Device::get_silence();

        if(active_key_list.size())
        {
          auto   it = active_key_list.begin();
          auto  end = active_key_list.end();

            while(it != end)
            {
              auto  k = *it;

                if(k->button->get_module().test_pressing())
                {
                  v += k->device.get_sample();

                  k->device.advance();

                  ++it;
                }

              else
                {
                  it = active_key_list.erase(it);
                }
            }
        }


        if(!noise.is_muted())
        {
          v += noise.get_sample();

          noise.advance();
        }


      *dst = clamp(v);

        if(mon)
        {
          mon->push(*dst);
        }


      dst += 1;
    }


    if(mon)
    {
      mon->need_to_redraw();
    }
}




}




