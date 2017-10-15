/**
 * \file SumFilter.h
 */

#ifndef ATK_TOOLS_SUMFILTER_H
#define ATK_TOOLS_SUMFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Sums two signals together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT SumFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
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
    SumFilter(std::size_t nb_output_channels = 1, std::size_t summed_channels = 2);
    /// Destructor
    ~SumFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const final;
  private:
    std::size_t summed_channels;
  };
}

#endif
