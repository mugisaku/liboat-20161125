#include"oat_buttonmodule.hpp"
#include<vector>




namespace oat{


namespace{
constexpr int   pressing_flag =  1;
constexpr int    pressed_flag =  2;
constexpr int  unpressed_flag =  4;
constexpr int   freezing_flag =  8;
constexpr int     toggle_flag = 16;
constexpr int     opened_flag = 32;
constexpr int       held_flag = 64;


std::vector<ButtonModule*>
changed_buttons;
}


void  ButtonModule::set_index(int  i)      {index = 0;}
int   ButtonModule::get_index(      ) const{return index;}


bool  ButtonModule::test_pressing()  const{return test(pressing_flag);}
bool  ButtonModule::test_freezing()  const{return test(freezing_flag);}
bool  ButtonModule::test_pressed()   const{return test(pressed_flag);}
bool  ButtonModule::test_unpressed() const{return test(unpressed_flag);}
bool  ButtonModule::test_toggle() const{return test(toggle_flag);}


void
ButtonModule::
press()
{
    if(!test_freezing())
    {
        if(test_toggle())
        {
          set(opened_flag);
        }


        if(!test_pressing())
        {
          set( pressed_flag);
          set(pressing_flag);

          changed_buttons.emplace_back(this);
        }
    }
}


void
ButtonModule::
unpress()
{
    if(!test_freezing())
    {
        if(test(opened_flag))
        {
            if(test(held_flag)){unset(held_flag);}
          else                 {  set(held_flag);}


          unset(opened_flag);
        }


        if(test_pressing() && !test(held_flag))
        {
            set(unpressed_flag);
          unset( pressing_flag);

          changed_buttons.emplace_back(this);
        }
    }
}


void  ButtonModule::freeze()  {  set(freezing_flag);}
void  ButtonModule::unfreeze(){unset(freezing_flag);}


void
ButtonModule::
use_toggle()
{
    set(toggle_flag);
  unset(opened_flag);
}


void
ButtonModule::
unuse_toggle()
{
  unset(toggle_flag);
  unset(opened_flag);
  unset(  held_flag);
}




void
ButtonModule::
unset_shortlived()
{
  unset(  pressed_flag);
  unset(unpressed_flag);
}




void
ButtonModule::
unset_shortlived_all()
{
    for(auto  b: changed_buttons)
    {
      b->unset_shortlived();
    }


  changed_buttons.clear();
}


}




