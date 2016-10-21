#include"pwg_wave.hpp"
#include"pwg_device.hpp"




namespace pwg{




Wave::
Wave(const char*  path)
{
  file = fopen(path,"wb");

    if(!file)
    {
      printf("%sは開けませんでした\n",path);

      throw path;
    }


  fwrite("RIFF",4,1,file);

  fgetpos(file,&riff_size_pos);

  fput32le(0);

  fwrite("WAVE",4,1,file);
  fwrite("fmt ",4,1,file);

  fput32le(                          16);//fmtチャンクサイズ
  fput16le(                           1);//フォーマットID
  fput16le(                           1);//チャンネル数
  fput32le(sample_rate                 );//サンプリングレート
  fput32le(sample_rate*sizeof(sample_t));//1秒間のデータサイズ
  fput16le(            sizeof(sample_t));//ブロックサイズ
  fput16le(                          16);//サンプルのビット数

  fwrite("data",4,1,file);

  fgetpos(file,&data_size_pos);

  fput32le(0);

  header_size = ftell(file);
}


Wave::
~Wave()
{
    if(file)
    {
      fclose(file);
    }
}




void
Wave::
fput16le(uint16_t  i)
{
  fputc((i   )&0xFF,file);
  fputc((i>>8)&0xFF,file);
}


void
Wave::
fput32le(uint32_t  i)
{
  fputc((i    )&0xFF,file);
  fputc((i>> 8)&0xFF,file);
  fputc((i>>16)&0xFF,file);
  fputc((i>>24)&0xFF,file);
}


void
Wave::
finish()
{
  auto  size = ftell(file);

  fsetpos(file,&riff_size_pos);

  fput32le(size-8);

  fsetpos(file,&data_size_pos);

  fput32le(size-header_size);
}




}




