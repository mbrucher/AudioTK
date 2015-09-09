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
  AttackReleaseHysteresisFilter<DataType_>::AttackReleaseHysteresisFilter(int nb_channels)
  :Parent(nb_channels, nb_channels), attack(1), release(1), hysteresis(1)
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
  void AttackReleaseHysteresisFilter<DataType_>::set_hysteresis(DataType_ hysteresis)
  {
    if(hysteresis < 0)
    {
      throw std::out_of_range("Hysteresis factor must be positive value");
    }
    if(hysteresis > 1)
    {
      throw std::out_of_range("Hysteresis factor must be less than 1");
    }
    this->hysteresis = hysteresis;
  }

  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::set_hysteresis_db(DataType_ hysteresis_db)
  {
    if(hysteresis_db > 0)
    {
      throw std::out_of_range("Hysteresis factor in dB must be less than 0");
    }
    set_hysteresis(std::pow(10., hysteresis_db/20));
  }

  template<typename DataType_>
  DataType_ AttackReleaseHysteresisFilter<DataType_>::get_hysteresis() const
  {
    return hysteresis;
  }

  template<typename DataType_>
  void AttackReleaseHysteresisFilter<DataType_>::process_impl(int64_t size) const
  {
    assert(nb_input_ports == nb_output_ports);
    for(int channel = 0; channel < nb_input_ports; ++channel)
    {
      const DataType* ATK_RESTRICT input = converted_inputs[channel];
      DataType* ATK_RESTRICT output = outputs[channel];
      for(int64_t i = 0; i < size; ++i)
      {
        if(output[i-1] < input[i])
        {
          output[i] = (1 - attack) * input[i] + attack * output[i-1];//attack phase
        }
        else
        {
          if(output[i-1] * hysteresis > input[i])
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
