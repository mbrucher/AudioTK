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
    using Parent = TypedBaseFilter<DataType_>;
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
    explicit BufferFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~BufferFilter() override;
  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
