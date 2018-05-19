/**
 * \file CachedSinusGeneratorFilter.cpp
 */

#include <ATK/Tools/CachedSinusGeneratorFilter.h>

#include <cmath>
#include <cstdint>
#include <cstring>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  CachedSinusGeneratorFilter<DataType_>::CachedSinusGeneratorFilter(int periods, int seconds)
  :Parent(0, 1), indice(1), periods(periods), seconds(seconds), volume(1), offset(0)
  {
  }
  
  template<typename DataType_>
  CachedSinusGeneratorFilter<DataType_>::~CachedSinusGeneratorFilter()
  {
  }
    
  template<typename DataType_>
  void CachedSinusGeneratorFilter<DataType_>::set_frequency(int periods, int seconds)
  {
    if(periods <= 0)
    {
      throw std::out_of_range("Periods must be strictly positive");
    }
    this->periods = periods;
    this->seconds = seconds;
    setup();
  }
  
  template<typename DataType_>
  std::pair<int, int> CachedSinusGeneratorFilter<DataType_>::get_frequency() const
  {
    return std::make_pair(periods, seconds);
  }

  template<typename DataType_>
  void CachedSinusGeneratorFilter<DataType_>::set_volume(DataType_ volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  DataType_ CachedSinusGeneratorFilter<DataType_>::get_volume() const
  {
    return volume;
  }
  
  template<typename DataType_>
  void CachedSinusGeneratorFilter<DataType_>::set_offset(DataType_ offset)
  {
    this->offset = offset;
  }
  
  template<typename DataType_>
  DataType_ CachedSinusGeneratorFilter<DataType_>::get_offset() const
  {
    return offset;
  }

  template<typename DataType_>
  void CachedSinusGeneratorFilter<DataType_>::setup()
  {
    indice = 0;
    cache.resize(output_sampling_rate * seconds);
    for(gsl::index i = 0; i < cache.size(); ++i)
    {
      cache[i] = static_cast<DataType>(std::sin(2 * boost::math::constants::pi<double>() * (i+1) * periods / seconds / output_sampling_rate));
    }
  }

  template<typename DataType_>
  void CachedSinusGeneratorFilter<DataType_>::process_impl(gsl::index size) const
  {
    DataType* ATK_RESTRICT output = outputs[0];
    gsl::index processed = 0;
    while (processed < size)
    {
      auto to_copy = std::min(size - processed, static_cast<gsl::index>(cache.size()) - indice);
      memcpy(reinterpret_cast<void*>(output + processed), reinterpret_cast<const void*>(cache.data() + indice), to_copy * sizeof(DataType_));
      indice += to_copy;
      processed += to_copy;
      if (indice >= cache.size())
      {
        indice = 0;
      }
    }
    for (gsl::index i = 0; i < size; ++i)
    {
      output[i] = static_cast<DataType>(offset + volume * output[i]);
    }
  }

  template class CachedSinusGeneratorFilter<std::int16_t>;
  template class CachedSinusGeneratorFilter<std::int32_t>;
  template class CachedSinusGeneratorFilter<int64_t>;
  template class CachedSinusGeneratorFilter<float>;
  template class CachedSinusGeneratorFilter<double>;
}
