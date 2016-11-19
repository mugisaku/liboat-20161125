#include"mg_core.hpp"




namespace core{


namespace{


std::vector<uint8_t>  copy_buffer;



std::vector<uint8_t>::const_iterator
copy()
{
  static std::vector<uint8_t>  buffer;

  buffer.clear();
  
    for(int  y = 0;  y < get_chip_height();  ++y){
    for(int  x = 0;  x < get_chip_width() ;  ++x){
      buffer.emplace_back(get_chip_pixel(x,y));
    }}


  return buffer.cbegin();
}


}




void
copy_chip()
{
  copy_buffer.clear();

    for(int  y = 0;  y < get_chip_height();  ++y){
    for(int  x = 0;  x < get_chip_width() ;  ++x){
      copy_buffer.emplace_back(get_chip_pixel(x,y));
    }}
}


void
paste_chip(bool  overwrite)
{
    if(copy_buffer.size())
    {
      auto  it = copy_buffer.cbegin();

        for(int  y = 0;  y < get_chip_height();  ++y){
        for(int  x = 0;  x < get_chip_width() ;  ++x){
          auto  v = *it++;

            if(overwrite || (v&8))
            {
              put_pixel(v,x,y);
            }
        }}


      update_because_of_image_changed();
    }
}


void
reverse_chip_horizontally()
{
  auto  it = copy();

    for(int  y = get_chip_height()-1;  y >=         0;  --y){
    for(int  x =             0;  x < get_chip_width();  ++x){
      put_pixel(*it++,x,y);
    }}


  update_because_of_image_changed();
}


void
reverse_chip_vertically()
{
  auto  it = copy();

    for(int  y =            0;  y < get_chip_height();  ++y){
    for(int  x = get_chip_width()-1;  x >=          0;  --x){
      put_pixel(*it++,x,y);
    }}


  update_because_of_image_changed();
}


void
mirror_chip_vertically()
{
    for(int  y = 0;  y < get_chip_height();  ++y)
    {
        for(int  x = 0;  x < get_chip_width()/2;  ++x)
        {
          auto  v = get_chip_pixel(x,y);

          put_pixel(v,get_chip_width()-1-x,y);
        }
    }


  update_because_of_image_changed();
}




void
shift_chip_up()
{
  auto  it = copy();

  it += get_chip_width();

    for(int  y = 0;  y < get_chip_height()-1;  ++y){
    for(int  x = 0;  x < get_chip_width()   ;  ++x){
      put_pixel(*it++,x,y);
    }}


  update_because_of_image_changed();
}


void
shift_chip_left()
{
  auto  it = copy();

    for(int  y = 0;  y < get_chip_height() ;  ++y)
    {
      ++it;

        for(int  x = 0;  x < get_chip_width()-1;  ++x)
        {
          put_pixel(*it++,x,y);
        }
    }


  update_because_of_image_changed();
}


void
shift_chip_right()
{
  auto  it = copy();

    for(int  y = 0;  y < get_chip_height() ;  ++y)
    {
        for(int  x = 1;  x < get_chip_width();  ++x)
        {
          put_pixel(*it++,x,y);
        }


      ++it;
    }


  update_because_of_image_changed();
}


void
shift_chip_down()
{
  auto  it = copy();

    for(int  y = 0;  y < get_chip_height()-1;  ++y){
    for(int  x = 0;  x < get_chip_width()   ;  ++x){
      put_pixel(*it++,x,y+1);
    }}


  update_because_of_image_changed();
}




void
clear_chip()
{
    for(int  y = 0;  y < get_chip_height();  ++y){
    for(int  x = 0;  x < get_chip_width() ;  ++x){
      put_pixel(0,x,y);
    }}


  update_because_of_image_changed();
}




}




