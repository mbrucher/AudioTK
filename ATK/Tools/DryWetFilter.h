/**
 * \file DryWetFilter.h
 */

#ifndef ATK_TOOLS_DRYWETFILTER_H
#define ATK_TOOLS_DRYWETFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Mixes two signals together
  template<typename DataType_>
  class ATK_TOOLS_EXPORT DryWetFilter final : public TypedBaseFilter<DataType_>
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
    DryWetFilter(int nb_channels = 1);
    /// Destructor
    ~DryWetFilter();

    /// Sets the amount of input signal in the output signal
    void set_dry(double dry);
    /// Returns the amount of dry signal in the output
    double get_dry() const;
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
    
  private:
    /// Amount of dry signal, between 0 and 1
    double dry;
  };
}

#endif
