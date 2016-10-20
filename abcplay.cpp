#include"pwg/pwg_wavedevice.hpp"
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


WaveDevice
dev(WaveKind::square,get_scale_frequency(0),2400);


void
callback(void*  userdata, uint8_t*  stream, int  len)
{
  auto  dst     = reinterpret_cast<sample_t*>(stream);
  auto  dst_end = dst+(len/2);

    for(auto  p = dst;  p < dst_end;  ++p)
    {
      *p = have.silence;
    }


    while(dst < dst_end)
    {
      *dst++ = dev.get_sample();

      dev.advance();
    }
}


#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


char
filepath[256];


uint32_t
finished_time;


void
read(FILE*  f)
{
  std::string  s;

    for(;;)
    {
      int  c = fgetc(f);

        if(feof(f))
        {
          break;
        }


      s.push_back(c);
    }


  fclose(f);

  SDL_PauseAudio(1);

  dev.clear_note();

  dev.append_note(s.data());

  dev.rewind_step();

  dev.unmute();
  dev.start();

  SDL_PauseAudio(0);
}


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
    if(!dev.is_running())
    {
      auto  now = SDL_GetTicks();

        if(now < (finished_time+1000))
        {
          return;
        }


      auto  f = fopen(filepath,"rb");

        if(f)
        {
          read(f);
        }

      else
        {
          printf("%sが開けませんでした\n",filepath);

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
      auto  f = fopen(filepath,"rb");

        if(!f)
        {
          printf("%sを開けませんでした\n",filepath);

          quit(0);
        }


      read(f);
    }


  std::signal(SIGINT ,quit);
  std::signal(SIGTERM,quit);

  dev.set_callback(finish);

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




