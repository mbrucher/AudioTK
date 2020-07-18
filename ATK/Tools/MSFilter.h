/**
 * \file MSFilter.h
 */

#ifndef ATK_TOOLS_MSFILTER_H
#define ATK_TOOLS_MSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Tools/config.h>

namespace ATK
{
  /// A middle side filter, splitting L/R signals in (L+R) and (L-R)
  template<typename DataType_>
  class ATK_TOOLS_EXPORT MiddleSideFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_output_ports;
    using Parent::nb_input_ports;
    
  public:
    /*!
    * @brief Constructor
    */
    explicit MiddleSideFilter(gsl::index nb_channels = 1);
    /// Destructor
    ~MiddleSideFilter() override = default;
    
  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
