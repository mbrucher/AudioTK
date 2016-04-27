/**
 * \file BufferFilter.h
 */

#ifndef ATK_TOOLS_BUFFERFILTER_H
#define ATK_TOOLS_BUFFERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Buffers input signals
  template<typename DataType_>
  class ATK_TOOLS_EXPORT BufferFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    BufferFilter(int nb_channels = 1);
    /// Destructor
    ~BufferFilter();
  protected:
    virtual void process_impl(int64_t size) const override final;
  };
}

#endif
