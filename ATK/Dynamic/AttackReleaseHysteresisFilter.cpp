/**
 * \file AttackReleaseHysteresisFilter.cpp
 */

#include "AttackReleaseHysteresisFilter.h"
#include <ATK/Core/Utilities.h>

#include <cassert>
#include <cmath>
#include <cstdint>

namespace ATK
{
  template<typename DataType_>
  AttackReleaseHysteresisFilter<DataType_>::AttackReleaseHysteresisFilter(gsl::index nb_channels)
  :Parent(nb_channels, nb_channels)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_attack(DataType_ attack)
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
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_attack() const
  {
    return attack;
  }

  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_release(DataType_ release)
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
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_release() const
  {
    return release;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_attack_hysteresis(DataType_ attack_hysteresis)
  {
    if(attack_hysteresis < release_hysteresis)
    {
      throw ATK::RuntimeError("Attack hysteresis factor must be bigger than release hysteresis");
    }
    if(attack_hysteresis > 1)
    {
      throw ATK::RuntimeError("Attack hysteresis factor must be smaller than 1");
    }
    this->attack_hysteresis = attack_hysteresis;
  }

  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_attack_hysteresis_db(DataType_ attack_hysteresis_db)
  {
    set_attack_hysteresis(static_cast<DataType_>(std::pow(10., attack_hysteresis_db/20)));
  }

  template<typename DataType_>
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_attack_hysteresis() const
  {
    return attack_hysteresis;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_release_hysteresis(DataType_ release_hysteresis)
  {
    if(release_hysteresis < 0)
    {
      throw ATK::RuntimeError("Release hysteresis factor must be positive");
    }
    if(release_hysteresis > 1)
    {
      throw ATK::RuntimeError("Release hysteresis factor must be smaller than 1");
    }
    this->release_hysteresis = release_hysteresis;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_release_hysteresis_db(DataType_ release_hysteresis_db)
  {
    set_release_hysteresis(static_cast<DataType_>(std::pow(10., release_hysteresis_db/20)));
  }
  
  template<typename DataType_>
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_release_hysteresis() const
  {
    return release_hysteresis;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::process_impl(gsl::index size) const
  {
    assert(nb_input_ports == nb_output_ports);
    for(gsl::index channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(gsl::index i = 0; i < size; ++i)
      {
        if(output[i-1] * attack_hysteresis < input[i])
        {
          output[i] = (1 - attack) * input[i] + attack * output[i-1];//attack phase
        }
        else
        {
          if(output[i-1] * release_hysteresis > input[i])
          {
            output[i] = (1 - release) * input[i] + release * output[i-1];//release phase
          }
          else
          {
            output[i] = output[i-1];
          }
        }
      }
    }
  }
  
#if ATK_ENABLE_INSTANTIATION
  template class AttackReleaseHysteresisFilter<float>;
#endif
  template class AttackReleaseHysteresisFilter<double>;
}
