/**
 * \file OutSndFileFilter.h
 */

#ifndef ATK_IO_SNDFILETRAITS_H
#define ATK_IO_SNDFILETRAITS_H

#include <cstdint>
#include <sndfile.h>

namespace ATK
{
  template<typename DataType>
  struct SndfileTraits
  {
  };

  template<>
  struct SndfileTraits<std::int16_t>
  {
    static int get_type()
    {
      return SF_FORMAT_PCM_16;
    }
  };
  
  template<>
  struct SndfileTraits<std::int32_t>
  {
    static int get_type()
    {
      return SF_FORMAT_PCM_32;
    }
  };
  
  template<>
  struct SndfileTraits<float>
  {
    static int get_type()
    {
      return SF_FORMAT_FLOAT;
    }
  };

  template<>
  struct SndfileTraits<double>
  {
    static int get_type()
    {
      return SF_FORMAT_DOUBLE;
    }
  };
}

#endif
