/**
 * \file SinusGeneratorFilter.cpp
 */

#include "SimpleSinusGeneratorFilter.h"

#include <cmath>
#include <cstdint>

#include <boost/math/constants/constants.hpp>

namespace ATK
{
  template<class DataType_>
  SimpleSinusGeneratorFilter<DataType_>::SimpleSinusGeneratorFilter()
  :TypedBaseFilter<DataType_>(0, 1), state(0), amplitude(1), frequency(1)
  {
  }
  
  template<class DataType_>
  SimpleSinusGeneratorFilter<DataType_>::~SimpleSinusGeneratorFilter()
  {
  }
  
  template<class DataType_>
  void SimpleSinusGeneratorFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }
  
  template<class DataType_>
  void SimpleSinusGeneratorFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }
  
  template<class DataType_>
  void SimpleSinusGeneratorFilter<DataType_>::process_impl(int64_t size) const
  {    
    double real_increment = 2. / output_sampling_rate * frequency;
    
    for(int64_t i = 0; i < size; ++i)
    {
      state += real_increment;
      outputs[0][i] = static_cast<DataType_>(amplitude * std::sin(state * boost::math::constants::pi<double>()));
    }
  }
  
  template class SimpleSinusGeneratorFilter<std::int16_t>;
  template class SimpleSinusGeneratorFilter<std::int32_t>;
  template class SimpleSinusGeneratorFilter<int64_t>;
  template class SimpleSinusGeneratorFilter<float>;
  template class SimpleSinusGeneratorFilter<double>;
}
