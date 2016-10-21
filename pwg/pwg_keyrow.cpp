#include"pwg_keyrow.hpp"
#include"pwg_keyboard.hpp"




namespace pwg{




namespace{
void
callback(oat::Button&  btn)
{
  auto&  key = *static_cast<Key*>(btn.get_userdata());

    if(btn.get_module().test_pressed())
    {
      SDL_LockAudio();

      key.device.reset_play_counter(sample_rate*20);
      key.device.start();
      key.device.unmute();

      key.board.push(&key);

      SDL_UnlockAudio();
    }

  else
    if(btn.get_module().test_unpressed())
    {
      SDL_LockAudio();

      key.device.stop();
      key.device.mute();

      SDL_UnlockAudio();
    }
}
}




KeyRow::
KeyRow(Keyboard&  brd, WaveKind  k)
{
  constexpr int  vol = 8000;

  keys[0] = new Key(brd,u"ド"  ,k,get_scale_frequency(-9),vol);
  keys[1] = new Key(brd,u"レ"  ,k,get_scale_frequency(-7),vol);
  keys[2] = new Key(brd,u"ミ"  ,k,get_scale_frequency(-5),vol);
  keys[3] = new Key(brd,u"ファ",k,get_scale_frequency(-4),vol);
  keys[4] = new Key(brd,u"ソ"  ,k,get_scale_frequency(-2),vol);
  keys[5] = new Key(brd,u"ラ"  ,k,get_scale_frequency( 0),vol);
  keys[6] = new Key(brd,u"シ"  ,k,get_scale_frequency( 2),vol);
  keys[7] = new Key(brd,u"ド"  ,k,get_scale_frequency( 3),vol);

    for(auto  ptr: keys)
    {
      ptr->button->set_callback(callback);
      ptr->button->set_userdata(ptr);
    }
}




Key*
KeyRow::
get_key(int  i) const
{
  return keys[i];
}


oat::TableRow*
KeyRow::
create_table(const char16_t*  text)
{
  std::vector<oat::Widget*>  rowsrc;

  rowsrc.emplace_back(new oat::Text(text));

    for(auto  key: keys)
    {
      rowsrc.emplace_back(key->button);
    }


  return new oat::TableRow(rowsrc);
}




}




