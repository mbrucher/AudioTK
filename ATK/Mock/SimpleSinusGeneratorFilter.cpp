/**
 * \file SinusGeneratorFilter.cpp
 */

#include "SimpleSinusGeneratorFilter.h"

#include <boost/math/constants/constants.hpp>

#include <cmath>
#include <cstdint>

namespace ATK
{
  template<class DataType_>
  SimpleSinusGeneratorFilter<DataType_>::SimpleSinusGeneratorFilter()
  :TypedBaseFilter<DataType_>(0, 1)
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
  void SimpleSinusGeneratorFilter<DataType_>::process_impl(gsl::index size) const
  {    
    double real_increment = 2. / output_sampling_rate * frequency;
    
    for(gsl::index i = 0; i < size; ++i)
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
