/**
 * \file ComplexConvertFilter.h
 */

#ifndef ATK_CORE_COMPLEXCONVERTFILTER_H
#define ATK_CORE_COMPLEXCONVERTFILTER_H

#include <complex>

#include "TypedBaseFilter.h"
#include "config.h"

namespace ATK
{
  /// Converts two real channels into a complex one
  template<typename DataType_>
  class ATK_CORE_EXPORT RealToComplexFilter final : public TypedBaseFilter<DataType_, std::complex<DataType_>>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_, std::complex<DataType_>> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
     */
    RealToComplexFilter(int nb_channels = 1);
    /// Destructor
    ~RealToComplexFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };

  /// Converts a complex channels into a two real one
  template<typename DataType_>
  class ATK_CORE_EXPORT ComplexToRealFilter final : public TypedBaseFilter<std::complex<DataType_>, DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<std::complex<DataType_>, DataType_> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of channels, equal to the number of input channels, half the number of output ones
    */
    ComplexToRealFilter(int nb_channels = 1);
    /// Destructor
    ~ComplexToRealFilter();

  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
