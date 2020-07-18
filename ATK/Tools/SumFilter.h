/**
 * \file SumFilter.h
 */

#ifndef ATK_TOOLS_SUMFILTER_H
#define ATK_TOOLS_SUMFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Sums two signals together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SumFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /// Constructor
    /**
     * @param nb_output_channels is the number of output channels
     * @param summed_channels is the number of input channels summed in one output channel
     */
    SumFilter(gsl::index nb_output_channels = 1, gsl::index summed_channels = 2);
    /// Destructor
    ~SumFilter() override = default;
    
  protected:
    void process_impl(gsl::index size) const final;
  private:
    gsl::index summed_channels;
  };
}

#endif
