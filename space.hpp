#ifndef _SPACE_HPP
#define _SPACE_HPP


#include<cstdint>
#include<cstdlib>
#include<cstring>
#include<list>
#include<vector>


#ifndef report
#define report  printf("[%8ld] %s %4d %s\n",time(nullptr),__FILE__,__LINE__,__func__)
#define  printd(d)  printf("[printd] %s %8d\n",#d,(d))

#define  rep(v,n)  for(int  v =     0;  v <  (n);  ++v)
#define rrep(v,n)  for(int  v = (n)-1;  v >=  0 ;  --v)
#endif


class
Bitmap
{
  uint8_t*  buffer;

public:
  const int  width;
  const int  height;

  const int  right;


  Bitmap(int  w, int  h):
  buffer(static_cast<uint8_t*>(malloc(w*h))), width(w), height(h), right(w-1){clear();}

  void  clear()
  {
    std::memset(buffer,0,width*height);
  }

  void  frame()
  {
      for(int  x = 0;  x < width;  ++x)
      {
        get(x,       0) = 0;
        get(x,height-1) = 0;
      }


      for(int  y = 0;  y < height;  ++y)
      {
        get(      0,y) = 0;
        get(width-1,y) = 0;
      }
  }

  uint8_t&  get(int  x, int  y) const{return buffer[(width*y)+x];}

};


struct
Space
{
  std::list<Space*>  uppers;
  std::list<Space*>  lowers;

  int  checked;

  int   left;
  int  right;

  int     top;
  int  bottom;

  int  liquid_level;

  Space(int  x, int  y);

  bool  operator<(const Space&  rhs) const;

  void  scan(std::vector<Space*>&  buf);

};


struct
SpaceManager
{
  using Group = std::vector<Space*>;

  std::list<Space>  spaces;

  std::vector<Group>  groups;

  int  scan_y=0;


  void  clear();

  void  scan(Bitmap&  bmp, Space&  sp);

  bool  convert(Bitmap&  bmp);

  void  link();

  void  make_group();

};


#endif




