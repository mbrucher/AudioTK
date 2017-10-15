/**
 * \file BufferFilter.h
 */

#ifndef ATK_TOOLS_BUFFERFILTER_H
#define ATK_TOOLS_BUFFERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Buffers input signals
  template<typename DataType_>
  class ATK_TOOLS_EXPORT BufferFilter final : public TypedBaseFilter<DataType_>
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
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    BufferFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~BufferFilter();
  protected:
    virtual void process_impl(std::size_t size) const final;
  };
}

#endif
