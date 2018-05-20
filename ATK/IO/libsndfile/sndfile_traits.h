/**
 * \file OutSndFileFilter.h
 */

#ifndef ATK_IO_SNDFILETRAITS_H
#define ATK_IO_SNDFILETRAITS_H

#include <cstdint>
#include <sndfile.h>

namespace ATK
{
  /// Empty traits
  template<typename DataType>
  class SndfileTraits
  {
  };

  /// Traits for integer 16bits
  template<>
  class SndfileTraits<std::int16_t>
  {
  public:
    static int get_type()
    {
      return SF_FORMAT_PCM_16;
    }
  };
  
  /// Traits for integer 32bits
  template<>
  class SndfileTraits<std::int32_t>
  {
  public:
    static int get_type()
    {
      return SF_FORMAT_PCM_32;
    }
  };
  
  /// Traits for float 32bits
  template<>
  class SndfileTraits<float>
  {
  public:
    static int get_type()
    {
      return SF_FORMAT_FLOAT;
    }
  };

  /// Traits for float 64bits
  template<>
  class SndfileTraits<double>
  {
  public:
    static int get_type()
    {
      return SF_FORMAT_DOUBLE;
    }
  };
}

#endif
