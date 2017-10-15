/**
 * \file DryWetFilter.h
 */

#ifndef ATK_TOOLS_DRYWETFILTER_H
#define ATK_TOOLS_DRYWETFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>
#include <ATK/Tools/ToolsInterface.h>

namespace ATK
{
  /// Mixes two signals together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT DryWetFilter final : public TypedBaseFilter<DataType_>, public DryWetInterface
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
    * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
    */
    DryWetFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~DryWetFilter();

    /// Sets the amount of input signal in the output signal
    void set_dry(double dry) final;
    /// Returns the amount of dry signal in the output
    double get_dry() const final;
    
  protected:
    virtual void process_impl(std::size_t size) const final;
    
  private:
    /// Amount of dry signal, between 0 and 1
    double dry;
  };
}

#endif
