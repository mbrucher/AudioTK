/**
 * \file TypedBaseFilter.cpp
 */

#include "TypedBaseFilter.h"

#include <cstdint>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/vector.hpp>

#include "Utilities.h"

namespace
{
  typedef boost::mpl::vector<std::int16_t, std::int32_t, std::int64_t, float, double> ConversionTypes;

  template<typename Vector, typename DataType>
  typename boost::enable_if<typename boost::mpl::empty<Vector>::type, void>::type
  convert_array(ATK::BaseFilter* filter, int port, DataType* converted_input, int size, int type)
  {
  }

  template<typename Vector, typename DataType>
  typename boost::disable_if<typename boost::mpl::empty<Vector>::type, void>::type
      convert_array(ATK::BaseFilter* filter, int port, DataType* converted_input, int size, int type)
  {
    if(type != 0)
    {
      convert_array<typename boost::mpl::pop_front<Vector>::type, DataType>(filter, port, converted_input, size, type - 1);
    }
    else
    {
      typedef typename boost::mpl::front<Vector>::type InputOriginalType;
      InputOriginalType* original_input_array = static_cast<ATK::TypedBaseFilter<InputOriginalType>*>(filter)->get_output_array(port);
      ATK::ConversionUtilities<InputOriginalType, DataType>::convert_array(original_input_array, converted_input, size);
    }
  }
}

namespace ATK
{
  template<typename DataType>
  TypedBaseFilter<DataType>::TypedBaseFilter(int nb_input_ports, int nb_output_ports)
  :Parent(nb_input_ports, nb_output_ports), converted_inputs(nb_input_ports), outputs(nb_output_ports)
  {
    converted_inputs_size.assign(nb_input_ports, 0);
    outputs_size.resize(nb_output_ports, 0);
  }

  template<typename DataType>
  TypedBaseFilter<DataType>::~TypedBaseFilter()
  {
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::process_impl(int size)
  {
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::prepare_process(int size)
  {
    convert_inputs(size);
  }

  template<typename DataType>
  int TypedBaseFilter<DataType>::get_type() const
  {
    return boost::mpl::distance<boost::mpl::begin<ConversionTypes>::type, typename boost::mpl::find<ConversionTypes, DataType>::type >::value;
  }

  template<typename DataType>
  DataType* TypedBaseFilter<DataType>::get_output_array(int port)
  {
    return outputs[port].get();
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::convert_inputs(int size)
  {
    for(int i = 0; i < nb_input_ports; ++i)
    {
      if(converted_inputs_size[i] < size)
      {
        converted_inputs[i].reset(new DataType[size]);
        converted_inputs_size[i] = size;
      }
      convert_array<ConversionTypes, DataType>(connections[i].second, connections[i].first, converted_inputs[i].get(), size, get_type());
    }
  }

  template class TypedBaseFilter<std::int16_t>;
  template class TypedBaseFilter<std::int32_t>;
  template class TypedBaseFilter<std::int64_t>;
  template class TypedBaseFilter<float>;
  template class TypedBaseFilter<double>;
}
