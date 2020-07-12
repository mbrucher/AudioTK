/**
 * \file DecimationFilter.h
 */

#ifndef ATK_TOOLS_DECIMATIONFILTER_H
#define ATK_TOOLS_DECIMATIONFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Slows the sampling rate of an input signal by a constant rate
  template<class DataType_>
  class ATK_TOOLS_EXPORT DecimationFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
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
    explicit DecimationFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~DecimationFilter()override;
    
  protected:
    void process_impl(gsl::index size) const final;
    void setup() final;
  };
}

#endif
