/**
 * \file TransistorClassAFilter.cpp
 */

#include "TransistorClassAFilter.h"

#include <cassert>

#include <ATK/Utility/VectorizedNewtonRaphson.h>

namespace ATK
{
  template <typename DataType_>
  class TransistorClassAFilter<DataType_>::TransistorClassAFunction
  {
  public:
    typedef DataType_ DataType;
  };
  
  template <typename DataType>
  TransistorClassAFilter<DataType>::TransistorClassAFilter()
    :Parent(1, 4)
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

    const DataType* ATK_RESTRICT input = converted_inputs[0];
    DataType* ATK_RESTRICT output_Vout = outputs[0];
    DataType* ATK_RESTRICT output_Vk = outputs[1];
    DataType* ATK_RESTRICT output_Vp = outputs[2];
    DataType* ATK_RESTRICT output_Vg = outputs[3];
    for(int64_t i = 0; i < size; ++i)
    {
      //optimizer->optimize(input + i, output_Vout + i, output_Vk + i, output_Vp + i, output_Vg + i);
    }
  }

  template class TransistorClassAFilter<float>;
  template class TransistorClassAFilter<double>;
}
