/**
 * \file AttackReleaseFilter.cpp
 */

#include "AttackReleaseFilter.h"
#include <ATK/Core/Utilities.h>

#include <cassert>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  AttackReleaseFilter<DataType_>::AttackReleaseFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
    output_delay = 1;
  }

  template<typename DataType_>
  void AttackReleaseFilter<DataType_>::set_attack(DataType_ attack)
  {
    if(attack < 0)
    {
      throw ATK::RuntimeError("Attack factor must be positive value");
    }
    if(attack > 1)
    {
      throw ATK::RuntimeError("Attack factor must be less than 1");
    }
    this->attack = attack;
  }
  
  template<typename DataType_>
  DataType_ AttackReleaseFilter<DataType_>::get_attack() const
  {
    return attack;
  }

  template<typename DataType_>
  void AttackReleaseFilter<DataType_>::set_release(DataType_ release)
  {
    if(release < 0)
    {
      throw ATK::RuntimeError("Release factor must be positive value");
    }
    if(release > 1)
    {
      throw ATK::RuntimeError("Release factor must be less than 1");
    }
    this->release = release;
  }

  template<typename DataType_>
  DataType_ AttackReleaseFilter<DataType_>::get_release() const
  {
    return release;
  }

  template<typename DataType_>
  void AttackReleaseFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        if(output[i-1] > input[i])
        {
          output[i] = (1 - release) * input[i] + release * output[i-1];//release phase
        }
        else
        {
          output[i] = (1 - attack) * input[i] + attack * output[i-1];//attack phase
        }
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class AttackReleaseFilter<float>;
#endif
  template class AttackReleaseFilter<double>;
}
