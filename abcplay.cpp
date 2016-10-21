#include"pwg/pwg_box.hpp"
#include<SDL.h>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<csignal>
#include<string>




using namespace pwg;


SDL_AudioSpec  want;
SDL_AudioSpec  have;


Box
box;


void
callback(void*  userdata, uint8_t*  stream, int  len)
{
  auto  dst     = reinterpret_cast<sample_t*>(stream);
  auto  dst_end = dst+(len/2);

  box.mix(dst,dst_end);
}


#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


char
filepath[256];


uint32_t
finished_time;


void
quit(int  v)
{
  SDL_CloseAudio();

  SDL_Quit();

  printf("\nBye!\n\n");

  std::exit(0);
}


void
finish()
{
  finished_time = SDL_GetTicks();
}


void
main_loop()
{
    if(!box.active_device_number)
    {
      auto  now = SDL_GetTicks();

        if(now < (finished_time+1000))
        {
          return;
        }


        try
        {
          SDL_PauseAudio(1);

          box.clear();

          box.load(filepath);

          box.ready();

          SDL_PauseAudio(0);
        }


        catch(...)
        {
          std::raise(SIGINT);
        }
    }


}


int
main(int  argc,  char**  argv)
{
    if(argc != 2)
    {
      printf("usage: abcplay FILE\n");

      return 0;
    }


  printf("abcplay - " __DATE__ "\n");

  SDL_Init(SDL_INIT_AUDIO);

  want.freq = sample_rate;
  want.format = AUDIO_S16SYS;
  want.channels = 1;
  want.samples = 1024;
  want.callback = callback;

  SDL_OpenAudio(&want,&have);

  Device::change_silence(have.silence);

    if(sscanf(argv[1],"%256s",filepath) == 1)
    {
        try
        {
          box.load(filepath);

          box.ready();
        }


        catch(...)
        {
          quit(0);
        }
    }


  std::signal(SIGINT ,quit);
  std::signal(SIGTERM,quit);

  box.finish = (finish);

  SDL_PauseAudio(0);

  printf("Ctrl+Cで終了\n");

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,-1,false);
#else
    for(;;)
    {
      main_loop();

      SDL_Delay(20);
    }
#endif


  return 0;
}




