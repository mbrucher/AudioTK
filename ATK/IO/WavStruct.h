/**
 * \file WavStruct.h
 */
  
#ifndef ATK_IO_WAVSTRUCT_H
#define ATK_IO_WAVSTRUCT_H

#include <cstdint>

namespace ATK
{
  struct WavHeader
  {
    char FileTypeBlocID[4];
    std::int32_t FileSize;
    char FileFormatID[4];
  };
  
  struct WavFormat
  {
    char FormatBlocID[4];
    std::int32_t BlocSize;
    std::int16_t AudioFormat;
    std::int16_t NbChannels;
    std::int32_t Frequence;
    std::int32_t BytePerSec;
    std::int16_t BytePerBloc;
    std::int16_t BitsPerSample;
  };
  
  struct WavData
  {
    char DataBlocID[4];
    std::int32_t DataSize;
  };
  
  template<typename DataType>
  struct WavTraits
  {
  };
  
  template<>
  struct WavTraits<std::int16_t>
  {
    static int get_wav_type()
    {
      return 1;
    }
  };
  
  template<>
  struct WavTraits<float>
  {
    static int get_wav_type()
    {
      return 3;
    }
  };
  
  template<>
  struct WavTraits<double>
  {
    static int get_wav_type()
    {
      return 3;
    }
  };
}

#endif
