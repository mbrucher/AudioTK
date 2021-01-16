/**
 * \file ApplyGainFilter.h
 */

#ifndef ATK_TOOLS_APPLYGAINFILTER_H
#define ATK_TOOLS_APPLYGAINFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Multiplies two channels together
  /**
   * Gain applyer. Has twice as many inputs channels as it has output channels
   * Even channels are signal, odd channels are gains, results is the product of both
   */
  template<typename DataType_>
  class ATK_TOOLS_EXPORT ApplyGainFilter final : public TypedBaseFilter<DataType_>
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
     * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
     */
    explicit ApplyGainFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~ApplyGainFilter() override = default;
    
  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
