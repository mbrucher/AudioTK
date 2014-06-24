/**
 * \file AttackReleaseFilter.h
 */

#ifndef ATK_DYNAMIC_ATTACKREKEASEFILTER_H
#define ATK_DYNAMIC_ATTACKREKEASEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates an output signal with the filter power of the input (computed with an AR1)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT AttackReleaseFilter : public TypedBaseFilter<DataType_>
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

  public:
    AttackReleaseFilter(int nb_channels = 1);
    ~AttackReleaseFilter();

    void set_attack(DataType_ attack);
    DataType_ get_attack() const;
    void set_release(DataType_ release);
    DataType_ get_release() const;
    
  protected:
    virtual void process_impl(std::int64_t size);
    
  private:
    DataType_ attack;
    DataType_ release;
  };
}

#endif
