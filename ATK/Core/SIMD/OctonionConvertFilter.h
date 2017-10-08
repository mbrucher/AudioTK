/**
 * \file OctonionConvertFilter.h
 */

#ifndef ATK_CORE_OCTONIONCONVERTFILTER_H
#define ATK_CORE_OCTONIONCONVERTFILTER_H

#include <simdpp/simd.h>

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Core/config.h>

namespace ATK
{
  /// Converts two real channels into a complex one
  template<typename DataType_, typename SIMDType>
  class ATK_CORE_EXPORT RealToOctonionFilter final : public TypedBaseFilter<DataType_, SIMDType>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_, SIMDType> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of channels, equal to the number of output channels, half the number of input ones
     */
    RealToOctonionFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~RealToOctonionFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };

  /// Converts a complex channels into a two real one
  template<typename SIMDType, typename DataType__>
  class ATK_CORE_EXPORT OctonionToRealFilter final : public TypedBaseFilter<SIMDType, DataType__>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<SIMDType, DataType__> Parent;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of channels, equal to the number of input channels, half the number of output ones
    */
    OctonionToRealFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~OctonionToRealFilter();

  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
