#include"pwg/pwg_wavedevice.hpp"
#include"pwg/pwg_box.hpp"
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>




using namespace pwg;


Box
box;


int
main(int  argc,  char**  argv)
{
    if(argc != 2)
    {
      printf("usage: abc2wav FILE\n");

      return 0;
    }


  printf("abc2av - " __DATE__ "\n");

  Device::change_silence(0);

  box.load(argv[1]);

  box.save("__abc.wav");


  return 0;
}




