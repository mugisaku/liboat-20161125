#include"fcfont.hpp"
#include<cstdio>




namespace fcfont{




namespace{
Character
table[] =
{
#include"characters.txt"
};
}


Character*
Character::
embedded_table = table;


int
Character::
embedded_number = sizeof(table)/sizeof(*table);


Character*
Character::
pointer_table[0x10000];



void
Character::
reset_table()
{
    for(auto&  c: table)
    {
      pointer_table[c.unicode] = &c;
    }
}


void
Character::
print_table()
{
  printf("//characters\n");

    for(auto&  c: table)
    {
      printf("{0x%04X,{",c.unicode);

        for(int  i = 0;  i < size;  ++i)
        {
          printf("0x%02X,",c.data[i]);
        }


      printf("}},\n");
    }
}




namespace{
Combined
combined_table[] =
{
#include"combineds.txt"
};
}


Combined*
Combined::
embedded_table = combined_table;


int
Combined::
embedded_number = sizeof(combined_table)/sizeof(*combined_table);


Combined*
Combined::
pointer_table[0x10000];


void
Combined::
reset_table()
{
    for(auto&  c: combined_table)
    {
      pointer_table[c.unicode] = &c;
    }
}


void
Combined::
print_table()
{
  printf("//combineds\n");

    for(auto&  c: combined_table)
    {
      printf("{0x%04X,0x%04X,0x%04X},\n",c.unicode,c.upper,c.lower);
    }


  printf("//talls\n");

    for(auto&  c: combined_table)
    {
      printf("{0x%04X,{",c.unicode);

      auto&  upper = Character::pointer_table[c.upper];
      auto&  lower = Character::pointer_table[c.lower];

        for(auto  v: upper->data)
        {
          printf("0x%02X,",v);
        }


        for(auto  v: lower->data)
        {
          printf("0x%02X,",v);
        }


      printf("}},\n");
    }
}


}




