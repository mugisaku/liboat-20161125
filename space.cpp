#include"space.hpp"




Space::
Space(int  x, int  y):
checked(0),
left(x),
right(x),
bottom(y),
top(y),
liquid_level(0){}




bool
Space::
operator<(const Space&  rhs) const
{
    if(top < rhs.top)
    {
      return true;
    }


  return(left < rhs.left);
}


void
Space::
scan(std::vector<Space*>&  buf)
{
    if(!checked)
    {
      buf.emplace_back(this);

      checked = 1;

        for(auto  sp: uppers){sp->scan(buf);}
        for(auto  sp: lowers){sp->scan(buf);}
    }
}


void
SpaceManager::
clear()
{
  scan_y = 0;

  spaces.clear();
  groups.clear();
}


void
SpaceManager::
scan(Bitmap&  bmp, Space&  sp)
{
  auto&  y = sp.bottom;

    while(bmp.get(sp.right+1,y) == 1)
    {
      ++sp.right;
    }


  ++y;

    for(;;)
    {
      auto   left_p = &bmp.get(sp.left ,y);
      auto  right_p = &bmp.get(sp.right,y);

        while(left_p <= right_p)
        {
            if((*left_p++) != 1)
            {
              --y;

              goto FINISH;
            }
        }


      left_p = &bmp.get(sp.left,y);

        if((*( left_p-1) == 1) ||
           (*(right_p+1) == 1))
        {
          --y;

          break;
        }


      ++y;
    }


FINISH:
    for(int  y = sp.top ;  y <= sp.bottom;  ++y){
    for(int  x = sp.left;  x <= sp.right ;  ++x){
      bmp.get(x,y) = 2;
    }}
}


bool
SpaceManager::
convert(Bitmap&  bmp)
{
    while(scan_y < bmp.height)
    {
        for(int  x = 0;  x < bmp.width;  ++x)
        {
            if(bmp.get(x,scan_y) == 1)
            {
              spaces.emplace_back(x,scan_y);

              scan(bmp,spaces.back());

              return true;
            }
        }


      scan_y += 1;
    }


  return false;
}




void
SpaceManager::
link()
{
  spaces.sort();

    for(auto&  a: spaces){
    for(auto&  b: spaces){
        if(&a != &b)
        {
          int   left0 = a.left;
          int  right0 = a.right;
          int   left1 = b.left;
          int  right1 = b.right;

            if(left1 > left0)
            {
              std::swap( left0, left1);
              std::swap(right0,right1);
            }


            if((left1  >=  left0) &&
               (right1 <= right0))
            {
                   if(a.bottom == b.top   ){a.lowers.emplace_back(&b);}
              else if(a.top    == b.bottom){a.uppers.emplace_back(&b);}
            }
        }
    }}
}




void
SpaceManager::
make_group()
{
  groups.clear();

    for(auto&  sp: spaces)
    {
      Group  grp;

      sp.scan(grp);

        if(grp.size())
        {
          groups.emplace_back(std::move(grp));
        }
    }


    for(auto&  sp: spaces)
    {
      sp.checked = 0;
    }
}





