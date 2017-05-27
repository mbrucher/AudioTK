/**
 * \file MaxFilter.h
 */

#ifndef ATK_TOOLS_MAXFILTER_H
#define ATK_TOOLS_MAXFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Returns the maximum of two signals in one
  template<typename DataType_>
  class ATK_TOOLS_EXPORT MaxFilter final : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    */
    MaxFilter(std::size_t nb_channels = 1);
    /// Destructor
    ~MaxFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
