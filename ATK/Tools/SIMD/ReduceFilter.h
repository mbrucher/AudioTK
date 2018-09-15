/**
 * \file ReduceFilter.h
 */

#ifndef ATK_TOOLS_SIMD_REDUCEFILTER_H
#define ATK_TOOLS_SIMD_REDUCEFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Sum all SIMD vector lines in the input signal
  template<typename DataType_, typename DataType__>
  class ATK_TOOLS_EXPORT ReduceFilter final : public TypedBaseFilter<DataType_, DataType__>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_, DataType__> Parent;
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
    ReduceFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~ReduceFilter() override;

  protected:
    void process_impl(gsl::index size) const final;
  };
  
  /// Sum all SIMD vector lines in the input signal
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createReduceFilter(gsl::index nb_channels = 1);
}

#endif
