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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_output_ports;
    using Parent::nb_input_ports;
    
  public:
    /*!
    * @brief Constructor
    */
    MiddleSideFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~MiddleSideFilter() override;
    
  protected:
    void process_impl(std::size_t size) const final;
  };
}

#endif
