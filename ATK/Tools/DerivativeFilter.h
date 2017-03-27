/**
 * \file DerivativeFilter.h
 */

#ifndef ATK_TOOLS_DERIVATIVEFILTER_H
#define ATK_TOOLS_DERIVATIVEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Does a discrete derivation of the input channels
  template<typename DataType_>
  class ATK_TOOLS_EXPORT DerivativeFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
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
    DerivativeFilter(int nb_channels = 1);
    /// Destructor
    ~DerivativeFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
