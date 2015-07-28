/**
 * \file SinusGeneratorFilter.cpp
 */

#include "SinusGeneratorFilter.h"

#include <cmath>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<typename DataType_>
  SinusGeneratorFilter<DataType_>::SinusGeneratorFilter()
  :Parent(0, 2), volume(1), offset(0), frequency(0), frequ_cos(1), frequ_sin(0), cos(1), sin(0)
  {
  }
  
  template<typename DataType_>
  SinusGeneratorFilter<DataType_>::~SinusGeneratorFilter()
  {
  }
  
  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_frequency(DataType_ frequency)
  {
    this->frequency = frequency;
    this->frequ_cos = std::cos(2 * boost::math::constants::pi<DataType_>() * frequency / output_sampling_rate);
    this->frequ_sin = std::sin(2 * boost::math::constants::pi<DataType_>() * frequency / output_sampling_rate);
    setup();
  }
  
  template<typename DataType_>
  DataType_ SinusGeneratorFilter<DataType_>::get_frequency() const
  {
    return frequency;
  }

  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_volume(double volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  double SinusGeneratorFilter<DataType_>::get_volume() const
  {
    return volume;
  }
  
  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_offset(double offset)
  {
    this->offset = offset;
  }
  
  template<typename DataType_>
  double SinusGeneratorFilter<DataType_>::get_offset() const
  {
    return offset;
  }

  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::full_setup()
  {
    Parent::full_setup();
    cos = 1;
    sin = 0;
  }

  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::process_impl(int64_t size) const
  {
    DataType* ATK_RESTRICT output_cos = outputs[0];
    DataType* ATK_RESTRICT output_sin = outputs[1];

    for(int64_t i = 0; i < size; ++i)
    {
      auto new_cos = cos * frequ_cos - sin * frequ_sin;
      auto new_sin = cos * frequ_sin + sin * frequ_cos;

      cos = new_cos / (new_cos * new_cos + new_sin * new_sin);
      sin = new_sin / (new_cos * new_cos + new_sin * new_sin);

      output_cos[i] = volume * cos + offset;
      output_sin[i] = volume * sin + offset;
    }
  }
  
  template class SinusGeneratorFilter<float>;
  template class SinusGeneratorFilter<double>;
}
