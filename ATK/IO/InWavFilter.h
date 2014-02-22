/**
 * \file InWavFilter.h
 */

#ifndef ATK_IO_INWAVFILTER_H
#define ATK_IO_INWAVFILTER_H

#include <string>

#include <ATK/Core/TypedBaseFilter.h>

#include "WavStruct.h"

namespace ATK
{
  template<typename DataType_>
  class InWavFilter: public TypedBaseFilter<DataType_>
  {
  public:
    InWavFilter(const std::string& filename);
    
    void process_impl(long size);
  };
}
#endif
