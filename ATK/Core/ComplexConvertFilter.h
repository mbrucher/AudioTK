/**
 * \file ComplexConvertFilter.h
 */

#ifndef ATK_CORE_COMPLEXCONVERTFILTER_H
#define ATK_CORE_COMPLEXCONVERTFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/config.h>

#include <complex>

namespace ATK
{
  /// Converts two real channels into a complex one
  template<typename DataType_>
  class ATK_CORE_EXPORT RealToComplexFilter final : public TypedBaseFilter<DataType_, std::complex<DataType_>>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_, std::complex<DataType_>>;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
     */
    explicit RealToComplexFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~RealToComplexFilter() override = default;
    
  protected:
    void process_impl(gsl::index size) const final;
  };

  /// Converts a complex channels into a two real one
  template<typename DataType_>
  class ATK_CORE_EXPORT ComplexToRealFilter final : public TypedBaseFilter<std::complex<DataType_>, DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<std::complex<DataType_>, DataType_>;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of channels, equal to the number of input channels, half the number of output ones
    */
    explicit ComplexToRealFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~ComplexToRealFilter() override = default;

  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
