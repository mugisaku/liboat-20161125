#include"oat_font.hpp"
#include<algorithm>




namespace oat{
namespace font{




namespace{


const uint32_t
data[] = {
#include"oat_font_unicode.inc"
};


const uint32_t*
table[0x10000];


struct
Initializer
{
  Initializer();

};


Initializer::
Initializer()
{
  enum{
    fullwidth_start = 0xFF00,
    fullwidth_end   = 0xFF5F,
  };

  const uint32_t*          p =          data ;
  const uint32_t*  const end = std::end(data);

    while(p < end)
    {
      auto  ptr = &p[1];

      const auto  unicode = *p;

      table[unicode] = ptr;


      p += 1+size;
    }


    if(!table[' '])
    {
      table[' '] = table[u'　'];
    }


    if(!table['-'])
    {
      table['-'] = table[u'─'];
    }


    for(int  c = fullwidth_start;  c < fullwidth_end;  ++c)
    {
      auto&  dst = table[c-fullwidth_start+' '];

      auto  src = table[c];

        if(!dst)
        {
          dst = src;
        }
    }
}


Initializer
init;


}




const uint32_t*
get_data(int  c)
{
  return table[c];
}



}}





