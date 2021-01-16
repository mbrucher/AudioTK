/**
 * \file SinusGeneratorFilter.cpp
 */

#include "SinusGeneratorFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cmath>

namespace ATK
{
  template<typename DataType_>
  SinusGeneratorFilter<DataType_>::SinusGeneratorFilter()
  :Parent(0, 2)
  {
  }
  
  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_frequency(DataType_ frequency)
  {
    if(frequency <= 0)
    {
      throw std::out_of_range("Frequency must be strictly positive");
    }
    this->frequency = frequency;
    this->frequ_cos = std::cos(2 * boost::math::constants::pi<DataType_>() * frequency / output_sampling_rate);
    this->frequ_sin = std::sin(2 * boost::math::constants::pi<DataType_>() * frequency / output_sampling_rate);
  }
  
  template<typename DataType_>
  DataType_ SinusGeneratorFilter<DataType_>::get_frequency() const
  {
    return frequency;
  }

  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_volume(DataType_ volume)
  {
    this->volume = volume;
  }
  
  template<typename DataType_>
  DataType_ SinusGeneratorFilter<DataType_>::get_volume() const
  {
    return volume;
  }
  
  template<typename DataType_>
  void SinusGeneratorFilter<DataType_>::set_offset(DataType_ offset)
  {
    this->offset = offset;
  }
  
  template<typename DataType_>
  DataType_ SinusGeneratorFilter<DataType_>::get_offset() const
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
  void SinusGeneratorFilter<DataType_>::process_impl(gsl::index size) const
  {
    DataType* ATK_RESTRICT output_cos = outputs[0];
    DataType* ATK_RESTRICT output_sin = outputs[1];

    for(gsl::index i = 0; i < size; ++i)
    {
      auto new_cos = cos * frequ_cos - sin * frequ_sin;
      auto new_sin = cos * frequ_sin + sin * frequ_cos;
      auto norm = (new_cos * new_cos + new_sin * new_sin);

      cos = new_cos / norm;
      sin = new_sin / norm;

      output_cos[i] = volume * cos + offset;
      output_sin[i] = volume * sin + offset;
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class SinusGeneratorFilter<float>;
#endif
  template class SinusGeneratorFilter<double>;
}
