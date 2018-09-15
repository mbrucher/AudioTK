/**
 * \file BroadcastFilter.h
 */

#ifndef ATK_TOOLS_SIMD_BROADCASTFILTER_H
#define ATK_TOOLS_SIMD_BROADCASTFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// Broadcast an input signal to all SIMD vector lines
  template<typename DataType_, typename DataType__>
  class ATK_TOOLS_EXPORT BroadcastFilter final : public TypedBaseFilter<DataType_, DataType__>
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
    BroadcastFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~BroadcastFilter() override;

  protected:
    void process_impl(gsl::index size) const final;
  };
  
  /// Broadcast an input signal to all SIMD vector lines
  template<typename DataType, gsl::index VL>
  ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter(gsl::index nb_channels = 1);
}

#endif
