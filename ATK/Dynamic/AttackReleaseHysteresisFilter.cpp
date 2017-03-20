/**
 * \file AttackReleaseHysteresisFilter.cpp
 */

#include "AttackReleaseHysteresisFilter.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace ATK
{
  template<typename DataType_>
  AttackReleaseHysteresisFilter<DataType_>::AttackReleaseHysteresisFilter(unsigned int nb_channels)
  :Parent(nb_channels, nb_channels), attack(1), release(1), attack_hysteresis(1), release_hysteresis(1)
  {
    output_delay = 1;
  }
  
  template<typename DataType_>
  AttackReleaseHysteresisFilter<DataType_>::~AttackReleaseHysteresisFilter()
  {
  }

  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_attack(DataType_ attack)
  {
    if(attack < 0)
    {
      throw std::out_of_range("Attack factor must be positive value");
    }
    if(attack > 1)
    {
      throw std::out_of_range("Attack factor must be less than 1");
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
      throw std::out_of_range("Release factor must be positive value");
    }
    if(release > 1)
    {
      throw std::out_of_range("Release factor must be less than 1");
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
      throw std::out_of_range("Attack hysteresis factor must be bigger than release hysteresis");
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
      throw std::out_of_range("Release hysteresis factor must be positive");
    }
    if(release_hysteresis > 1)
    {
      throw std::out_of_range("Release hysteresis factor must be smaller than 1");
    }
    this->release_hysteresis = release_hysteresis;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_release_hysteresis_db(DataType_ release_hysteresis_db)
  {
    if(release_hysteresis_db < 0)
    {
      throw std::out_of_range("Release hysteresis factor in dB must be smaller than 0");
    }
    set_release_hysteresis(static_cast<DataType_>(std::pow(10., release_hysteresis_db/20)));
  }
  
  template<typename DataType_>
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_release_hysteresis() const
  {
    return release_hysteresis;
  }
  
  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::process_impl(std::size_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    for(unsigned int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(std::size_t i = 0; i < size; ++i)
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
  
  template class AttackReleaseHysteresisFilter<float>;
  template class AttackReleaseHysteresisFilter<double>;
}
