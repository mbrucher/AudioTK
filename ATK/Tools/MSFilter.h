/**
 * \file MSFilter.h
 */

#ifndef ATK_TOOLS_MSFILTER_H
#define ATK_TOOLS_MSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

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
    
  public:
    /*!
    * @brief Constructor
    */
    MiddleSideFilter();
    /// Destructor
    ~MiddleSideFilter();
    
  protected:
    virtual void process_impl(std::size_t size) const override final;
  };
}

#endif
