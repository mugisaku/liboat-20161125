#include"pwg_keyrow.hpp"
#include"pwg_keyboard.hpp"




namespace pwg{




namespace{
void
callback(oat::Button&  btn)
{
  auto&  key = *static_cast<Key*>(btn.get_userdata());

    if(btn.get_module().test_pressing())
    {
      SDL_LockAudio();

      key.device.reset();
      key.device.unmute();

      key.board.push(&key);

      SDL_UnlockAudio();
    }

  else
    {
      SDL_LockAudio();

      key.device.mute();

      SDL_UnlockAudio();
    }
}
}




KeyRow::
KeyRow(Keyboard&  brd, WaveKind  k)
{
  keys[0] = new Key(brd,u"ド"  ,k,get_scale_frequency(-9),2400);
  keys[1] = new Key(brd,u"レ"  ,k,get_scale_frequency(-7),2400);
  keys[2] = new Key(brd,u"ミ"  ,k,get_scale_frequency(-5),2400);
  keys[3] = new Key(brd,u"ファ",k,get_scale_frequency(-4),2400);
  keys[4] = new Key(brd,u"ソ"  ,k,get_scale_frequency(-2),2400);
  keys[5] = new Key(brd,u"ラ"  ,k,get_scale_frequency( 0),2400);
  keys[6] = new Key(brd,u"シ"  ,k,get_scale_frequency( 2),2400);
  keys[7] = new Key(brd,u"ド"  ,k,get_scale_frequency( 3),2400);

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




