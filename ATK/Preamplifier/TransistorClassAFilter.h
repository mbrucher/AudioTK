/**
 * \file TransistorClassAFilter.h
 */

#ifndef ATK_PREAMPLIFIER_TRANSISTORCLASSEAFILTER_H
#define ATK_PREAMPLIFIER_TRANSISTORCLASSEAFILTER_H

#include <list>
#include <vector>

#include <ATK/Preamplifier/config.h>

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// A class A transistor preamplifier (Ebers-Moll equations)
  template<typename DataType_>
  class ATK_PREAMPLIFIER_EXPORT TransistorClassAFilter: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_delay;
    using Parent::output_delay;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:

  public:
    /// Build a new convolution filter
    TransistorClassAFilter();
    
    void process_impl(int64_t size) const override final;
    
    void setup() override final;
  };
}

#endif
