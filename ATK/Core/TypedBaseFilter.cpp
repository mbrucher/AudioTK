/**
 * \file TypedBaseFilter.cpp
 */

#include "TypedBaseFilter.h"

#include <cstdint>

namespace ATK
{
  template<typename DataType>
  TypedBaseFilter<DataType>::TypedBaseFilter(int nb_input_ports, int nb_output_ports)
  :BaseFilter(nb_input_ports, nb_output_ports)
  {
  }

  template<typename DataType>
  TypedBaseFilter<DataType>::~TypedBaseFilter()
  {
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::process_impl()
  {
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::update_impl()
  {
  }

  template class TypedBaseFilter<std::int16_t>;
  template class TypedBaseFilter<std::int32_t>;
  template class TypedBaseFilter<std::int64_t>;
  template class TypedBaseFilter<float>;
  template class TypedBaseFilter<double>;
}
