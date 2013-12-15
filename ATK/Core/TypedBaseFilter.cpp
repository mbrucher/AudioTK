/**
 * \file TypedBaseFilter.cpp
 */

#include "TypedBaseFilter.h"

#include <cstdint>

#include <boost/mpl/vector.hpp>

namespace
{
  boost::mpl::vector<std::int16_t, std::int32_t, std::int64_t, float, double> ConversionTypes;
  
//  template<typename Vector>
//  void convert_array(
}

namespace ATK
{
  template<typename DataType>
  TypedBaseFilter<DataType>::TypedBaseFilter(int nb_input_ports, int nb_output_ports)
  :BaseFilter(nb_input_ports, nb_output_ports), converted_inputs(nb_input_ports), outputs(nb_output_ports)
  {
    converted_inputs_size.assign(nb_input_ports, 0);
    outputs_size.resize(nb_output_ports, 0);
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
  DataType* TypedBaseFilter<DataType>::get_output_array(int port, int size)
  {
    return outputs[port].get();
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::convert_inputs(int size)
  {
    for(int i = 0; i < nb_input_ports; ++i)
    {
      if(converted_inputs_size[i] > size)
      {
        converted_inputs[i].reset(new DataType[size]);
        converted_inputs_size[i] = size;
      }
      //convert_array(connections[i].second->get_output_array(connections[i].first, size), converted_inputs[i], size);
    }
  }

  template class TypedBaseFilter<std::int16_t>;
  template class TypedBaseFilter<std::int32_t>;
  template class TypedBaseFilter<std::int64_t>;
  template class TypedBaseFilter<float>;
  template class TypedBaseFilter<double>;
}
