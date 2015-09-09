/**
 * \file AttackReleaseHysteresisFilter.h
 */

#ifndef ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H
#define ATK_DYNAMIC_ATTACKRELEASEHYSTERESISFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates an output signal with the filter power of the input (computed with an AR1)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT AttackReleaseHysteresisFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    AttackReleaseHysteresisFilter(int nb_channels = 1);
    ~AttackReleaseHysteresisFilter();

    void set_attack(DataType_ attack);
    DataType_ get_attack() const;
    void set_release(DataType_ release);
    DataType_ get_release() const;
    void set_hysteresis(DataType_ hysteresis);
    void set_hysteresis_db(DataType_ hysteresis_db);
    DataType_ get_hysteresis() const;
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    DataType_ attack;
    DataType_ release;
    DataType_ hysteresis;
  };
}

#endif
