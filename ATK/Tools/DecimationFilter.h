/**
 * \file DecimationFilter.h
 */

#ifndef ATK_TOOLS_DECIMATIONFILTER_H
#define ATK_TOOLS_DECIMATIONFILTER_H

#include "../Core/TypedBaseFilter.h"
#include "config.h"

namespace ATK
{
  /// Slows the sampling rate of an input signal by a constant rate
  template<class DataType_>
  class ATK_TOOLS_EXPORT DecimationFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

    /// Decimation factor, also the ratio between input and output sampling rate
    int decimation;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    DecimationFilter(int nb_channels = 1);
    /// Destructor
    ~DecimationFilter();
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    void setup() override final;
  };
}

#endif
