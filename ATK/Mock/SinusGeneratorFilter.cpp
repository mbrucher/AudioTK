/**
 * \file SinusGeneratorFilter.cpp
 */

#include "SinusGeneratorFilter.h"

#include <cmath>
#include <cstdint>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<class DataType_>
  SinusGeneratorFilter<DataType_>::SinusGeneratorFilter()
  :TypedBaseFilter<DataType_>(0, 1), state(0), amplitude(1), frequency(1)
  {
  }
  
  template<class DataType_>
  SinusGeneratorFilter<DataType_>::~SinusGeneratorFilter()
  {
  }
  
  template<class DataType_>
  void SinusGeneratorFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void SinusGeneratorFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }
  
  template<class DataType_>
  void SinusGeneratorFilter<DataType_>::process_impl(long size)
  {    
    double real_increment = 2. / output_sampling_rate * frequency;
    
    for(long i = 0; i < size; ++i)
    {
      state += real_increment;
      outputs[0][i] = amplitude * std::sin(state * boost::math::constants::pi<double>());
    }
  }
  
  template class SinusGeneratorFilter<std::int16_t>;
  template class SinusGeneratorFilter<std::int32_t>;
  template class SinusGeneratorFilter<std::int64_t>;
  template class SinusGeneratorFilter<float>;
  template class SinusGeneratorFilter<double>;
}
