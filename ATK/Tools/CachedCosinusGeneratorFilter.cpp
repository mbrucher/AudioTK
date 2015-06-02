/**
 * \file CachedCosinusGeneratorFilter.cpp
 */

#include "CachedCosinusGeneratorFilter.h"

#include <cmath>
#include <cstdint>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  CachedCosinusGeneratorFilter<DataType_>::CachedCosinusGeneratorFilter(int periods, int seconds)
  :Parent(0, 1), indice(1), periods(periods), seconds(seconds), volume(1), offset(0)
  {
  }
  
  template<typename DataType_>
  CachedCosinusGeneratorFilter<DataType_>::~CachedCosinusGeneratorFilter()
  {
  }
  
  template<typename DataType_>
  void CachedCosinusGeneratorFilter<DataType_>::set_frequency(int periods, int seconds)
  {
    this->periods = periods;
    this->seconds = seconds;
    setup();
  }
  
  template<typename DataType_>
  std::pair<int, int> CachedCosinusGeneratorFilter<DataType_>::get_frequency() const
  {
    return std::make_pair(periods, seconds);
  }

  template<typename DataType_>
  void CachedCosinusGeneratorFilter<DataType_>::set_volume(double volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  double CachedCosinusGeneratorFilter<DataType_>::get_volume() const
  {
    return volume;
  }
  
  template<typename DataType_>
  void CachedCosinusGeneratorFilter<DataType_>::set_offset(double offset)
  {
    this->offset = offset;
  }
  
  template<typename DataType_>
  double CachedCosinusGeneratorFilter<DataType_>::get_offset() const
  {
    return offset;
  }

  template<typename DataType_>
  void CachedCosinusGeneratorFilter<DataType_>::setup()
  {
    indice = 0;
    cache.resize(output_sampling_rate * seconds);
    for(int i = 0; i < cache.size(); ++i)
    {
      cache[i] = static_cast<DataType>(std::cos(2 * boost::math::constants::pi<double>() * (i+1) * periods / seconds / output_sampling_rate));
    }
  }

  template<typename DataType_>
  void CachedCosinusGeneratorFilter<DataType_>::process_impl(std::int64_t size)
  {
    DataType* ATK_RESTRICT output = outputs[0];
    std::int64_t processed = 0;
    while(processed < size)
    {
      std::int64_t to_copy = std::min(size - processed, std::int64_t(cache.size()) - indice);
      memcpy(reinterpret_cast<void*>(output + processed), reinterpret_cast<const void*>(cache.data() + indice), to_copy * sizeof(DataType_));
      indice += to_copy;
      processed += to_copy;
      if(indice >= static_cast<int64_t>(cache.size()))
      {
        indice = 0;
      }
    }
    for(std::int64_t i = 0; i < size; ++i)
    {
      output[i] = static_cast<DataType>(offset + volume * output[i]);
    }
  }
  
  template class CachedCosinusGeneratorFilter<float>;
  template class CachedCosinusGeneratorFilter<double>;
}
