/**
 * \file TypedBaseFilter.cpp
 */

#include "TypedBaseFilter.h"

#include <cstdint>

#include <boost/mpl/distance.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/utility/enable_if.hpp>

#include "Utilities.h"

namespace
{
  const size_t alignment = 32;

  typedef boost::mpl::vector<std::int16_t, std::int32_t, int64_t, float, double> ConversionTypes;

  template<typename Vector, typename DataType>
  typename boost::enable_if<typename boost::mpl::empty<Vector>::type, void>::type
  convert_array(ATK::BaseFilter* filter, int port, DataType* converted_input, int64_t size, int type)
  {
  }

  template<typename Vector, typename DataType>
  typename boost::disable_if<typename boost::mpl::empty<Vector>::type, void>::type
      convert_array(ATK::BaseFilter* filter, int port, DataType* converted_input, int64_t size, int type)
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
  :Parent(nb_input_ports, nb_output_ports), converted_inputs_delay(nb_input_ports), converted_inputs(nb_input_ports, nullptr), converted_inputs_size(nb_input_ports, 0), outputs_delay(nb_output_ports), outputs(nb_output_ports, nullptr), outputs_size(nb_output_ports, 0), default_input(nb_input_ports, 0), default_output(nb_output_ports, 0)
  {
  }

  template<typename DataType>
  TypedBaseFilter<DataType>::TypedBaseFilter(TypedBaseFilter&& other)
  :Parent(std::move(other)), converted_inputs_delay(std::move(other.converted_inputs_delay)), converted_inputs(std::move(other.converted_inputs)), converted_inputs_size(std::move(other.converted_inputs_size)), outputs_delay(std::move(other.outputs_delay)), outputs(std::move(other.outputs)), outputs_size(std::move(other.outputs_size)), default_input(std::move(other.default_input)), default_output(std::move(other.default_output))
  {
    
  }

  template<typename DataType>
  TypedBaseFilter<DataType>::~TypedBaseFilter()
  {
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::set_nb_input_ports(int nb_ports)
  {
    if(nb_ports == nb_input_ports)
      return;
    Parent::set_nb_input_ports(nb_ports);
    converted_inputs_delay = std::vector<std::unique_ptr<DataType[]> >(nb_ports);
    converted_inputs.assign(nb_ports, nullptr);
    converted_inputs_size.assign(nb_ports, 0);
    default_input.assign(nb_ports, 0);
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::set_nb_output_ports(int nb_ports)
  {
    if(nb_ports == nb_output_ports)
      return;
    Parent::set_nb_output_ports(nb_ports);
    outputs_delay = std::vector<std::unique_ptr<DataType[]> >(nb_ports);
    outputs.assign(nb_ports, nullptr);
    outputs_size.assign(nb_ports, 0);
    default_output.assign(nb_ports, 0);
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::process_impl(int64_t size) const
  {
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::prepare_process(int64_t size)
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
    return outputs[port];
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::convert_inputs(int64_t size)
  {
    for(int i = 0; i < nb_input_ports; ++i)
    {
      if(input_delay <= connections[i].second->get_output_delay() && connections[i].second->get_type() == get_type())
      {
        converted_inputs[i] = reinterpret_cast<TypedBaseFilter<DataType>* >(connections[i].second)->get_output_array(connections[i].first);
        continue;
      }
      auto input_size = converted_inputs_size[i];
      if(input_size < size)
      {
        std::unique_ptr<DataType[]> temp(new DataType[static_cast<unsigned int>(input_delay + size + (alignment - 1) / sizeof(DataType))]);
        auto my_temp_ptr = reinterpret_cast<void*>(temp.get());
        size_t space;
        std::align(alignment, sizeof(DataType), my_temp_ptr, space);
        auto temp_ptr = reinterpret_cast<DataType*>(my_temp_ptr);
        if(input_size == 0)
        {
          for(int j = 0; j < input_delay; ++j)
          {
            temp_ptr[j] = default_input[i];
          }
        }
        else
        {
          const auto input_ptr = converted_inputs[i];
          for(int j = 0; j < input_delay; ++j)
          {
            temp_ptr[j] = input_ptr[last_size + j - input_delay];
          }
        }
        
        converted_inputs_delay[i] = std::move(temp);
        converted_inputs[i] = temp_ptr + input_delay;
        converted_inputs_size[i] = size;
      }
      else
      {
        auto my_last_size = last_size * input_sampling_rate / output_sampling_rate;
        const auto input_ptr = converted_inputs[i];
        for(int j = 0; j < input_delay; ++j)
        {
          input_ptr[j - input_delay] = input_ptr[my_last_size + j - input_delay];
        }
      }
      convert_array<ConversionTypes, DataType>(connections[i].second, connections[i].first, converted_inputs[i], size, connections[i].second->get_type());
    }
  }
  
  template<typename DataType>
  void TypedBaseFilter<DataType>::prepare_outputs(int64_t size)
  {
    for(int i = 0; i < nb_output_ports; ++i)
    {
      auto output_size = outputs_size[i];
      if(output_size < size)
      {
        std::unique_ptr<DataType[]> temp(new DataType[static_cast<unsigned int>(output_delay + size + (alignment - 1) / sizeof(DataType)]));
        auto my_temp_ptr = reinterpret_cast<void*>(temp.get());
        size_t space;
        std::align(alignment, sizeof(DataType), my_temp_ptr, space);
        auto temp_ptr = reinterpret_cast<DataType*>(my_temp_ptr);
        if(output_size == 0)
        {
          for(int j = 0; j < output_delay; ++j)
          {
            temp_ptr[j] = default_output[i];
          }
        }
        else
        {
          const auto output_ptr = outputs[i];
          for(int j = 0; j < output_delay; ++j)
          {
            temp_ptr[j] = output_ptr[last_size + j - output_delay];
          }
        }
        
        outputs_delay[i] = std::move(temp);
        outputs[i] = temp_ptr + output_delay;
        outputs_size[i] = size;
      }
      else
      {
        const auto output_ptr = outputs[i];
        for(int j = 0; j < output_delay; ++j)
        {
          output_ptr[j - output_delay] = output_ptr[last_size + j - output_delay];
        }
      }
    }
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::full_setup()
  {
    // Reset input arrays
    converted_inputs_delay = std::vector<std::unique_ptr<DataType[]> >(nb_input_ports);
    converted_inputs.assign(nb_input_ports, nullptr);
    converted_inputs_size.assign(nb_input_ports, 0);

    // Reset output arrays
    outputs_delay = std::vector<std::unique_ptr<DataType[]> >(nb_output_ports);
    outputs.assign(nb_output_ports, nullptr);
    outputs_size.assign(nb_output_ports, 0);

    Parent::full_setup();
  }

  template<typename DataType>
  void TypedBaseFilter<DataType>::set_input_port(int input_port, BaseFilter* filter, int output_port)
  {
    Parent::set_input_port(input_port, filter, output_port);
    converted_inputs_size[input_port] = 0;
  }

  template class TypedBaseFilter<std::int16_t>;
  template class TypedBaseFilter<std::int32_t>;
  template class TypedBaseFilter<int64_t>;
  template class TypedBaseFilter<float>;
  template class TypedBaseFilter<double>;
}
