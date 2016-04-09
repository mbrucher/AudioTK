/**
 * \file TransistorClassAFilter.cpp
 */

#include "TransistorClassAFilter.h"

#include <cassert>

namespace ATK
{
  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter()
    :Parent(1, 1)
  {
  }
  
  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::setup()
  {
    Parent::setup();
  }

  template<typename DataType_>
  void TransistorClassAFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(input_sampling_rate == output_sampling_rate);
  }

  template class TransistorClassAFilter<double>;
}
