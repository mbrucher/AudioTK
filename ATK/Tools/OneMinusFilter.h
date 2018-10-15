/**
 * \file OneMinusFilter.h
 */

#ifndef ATK_TOOLS_ONEMINUSFILTER_H
#define ATK_TOOLS_ONEMINUSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Computes 1 - input for all channels
  template<typename DataType_>
  class ATK_TOOLS_EXPORT OneMinusFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::output_delay;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    
  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    OneMinusFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~OneMinusFilter() override;
    
  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
