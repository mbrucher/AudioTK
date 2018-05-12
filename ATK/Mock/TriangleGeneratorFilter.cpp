/**
 * \file TriangleGeneratorFilter.cpp
 */

#include <ATK/Mock/TriangleGeneratorFilter.h>

#include <cstdint>
#include <complex>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<class DataType_>
  TriangleGeneratorFilter<DataType_>::TriangleGeneratorFilter()
  :TypedBaseFilter<DataType_>(0, 1), state(0), ascending(true), amplitude(1), frequency(1)
  {
  }
  
  template<class DataType_>
  TriangleGeneratorFilter<DataType_>::~TriangleGeneratorFilter()
  {
  }
  
  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::set_amplitude(DataType_ amplitude)
  {
    this->amplitude = amplitude;
  }

  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::set_frequency(int frequency)
  {
    this->frequency = frequency;
  }
  
  template<class DataType_>
  void TriangleGeneratorFilter<DataType_>::process_impl(std::size_t size) const
  {    
    double real_increment = 2. / output_sampling_rate * frequency;
    
    for(gsl::index i = 0; i < size; ++i)
    {
      state += real_increment * (ascending ? 1 : -1);
      if(state >= 1)
      {
        state -= 2 * real_increment;
        ascending = !ascending;
      }
      else if(state <= -1)
      {
        state += 2 * real_increment;
        ascending = !ascending;
      }
      outputs[0][i] = TypeTraits<DataType>::from_double(TypeTraits<DataType>::to_double(amplitude) * state);
    }
  }
  
  template class TriangleGeneratorFilter<std::int16_t>;
  template class TriangleGeneratorFilter<std::int32_t>;
  template class TriangleGeneratorFilter<std::int64_t>;
  template class TriangleGeneratorFilter<float>;
  template class TriangleGeneratorFilter<double>;
  template class TriangleGeneratorFilter<std::complex<float>>;
  template class TriangleGeneratorFilter<std::complex<double>>;
}
