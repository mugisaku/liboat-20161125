#ifndef OAT_UTIL_HPP
#define OAT_UTIL_HPP


#include<cstdint>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cstdarg>
#include<ctime>
#include<string>
#include<vector>
#include<algorithm>
#include<initializer_list>
#include<SDL.h>


#define report  printf("[%8ld] %s %4d %s\n",time(nullptr),__FILE__,__LINE__,__func__)
#define  printd(d)  printf("[printd] %s %8d\n",#d,(d))

#define  rep(v,n)  for(int  v =     0;  v <  (n);  ++v)
#define rrep(v,n)  for(int  v = (n)-1;  v >=  0 ;  --v)


using uint = unsigned int;


namespace oat{


extern const int  dirsepch;


struct
Point
{
  int16_t  x;
  int16_t  y;

};


struct
TwoPoints
{
  int16_t  x0;
  int16_t  y0;
  int16_t  x1;
  int16_t  y1;

};


SDL_Rect  make_rect(const TwoPoints&  points);

std::string  basename(const std::string&  s);

size_t   u16strlen(const char16_t*  str);

size_t   get_utf8_bytes(const char*  s);
size_t  get_utf8_length(const char*  s);

std::u16string  to_u16string(const std::string&     s);
std::string        to_string(const std::u16string&  u16s);

size_t  push_utf8(std::string  s, char16_t  c);


int  fputc16le(int  c, FILE*  f);
int  fputc32le(int  c, FILE*  f);

int  fgetc16le(FILE*  f);
int  fgetc32le(FILE*  f);


template<typename  T>
void
putc(int  c, T&  vec)
{
  vec.push_back((c   )&0xFF);
}


template<typename  T>
void
putc16le(int  c, T&  vec)
{
  vec.push_back((c   )&0xFF);
  vec.push_back((c>>8)&0xFF);
}


template<typename  T>
void
putc32le(int  c, T&  vec)
{
  vec.push_back((c    )&0xFF);
  vec.push_back((c>> 8)&0xFF);
  vec.push_back((c>>16)&0xFF);
  vec.push_back((c>>24)&0xFF);
}


template<typename  T>
int
getc(T&  it)
{
  return *it++;
}


template<typename  T>
int
getc16le(T&  it)
{
  uint16_t  v  = getc(it)   ;
            v |= getc(it)<<8;

  return(int16_t)(v);
}


template<typename  T>
int
getc32le(T&  it)
{
  uint32_t  v  = getc(it)    ;
            v |= getc(it)<< 8;
            v |= getc(it)<<16;
            v |= getc(it)<<24;

  return(int32_t)(v);
}


void    save_file(const void*  src_data, size_t  src_size, const char*  path);
void  save_gzfile(const void*  src_data, size_t  src_size, const char*  path);


std::vector<uint8_t>    load_file(const char*  path);
std::vector<uint8_t>  load_gzfile(const char*  path);

std::string  to_string(const char*  fmt, ...);


std::string           encode_base64(const void*  ptr, size_t  length);
std::vector<uint8_t>  decode_base64(const std::string&  s);


}




#endif




