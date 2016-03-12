/**
 * \file PowerFilter.h
 */

#ifndef ATK_DYNAMIC_POWERFILTER_H
#define ATK_DYNAMIC_POWERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// Creates an output signal with the filtered power of the input (computed with an AR1)
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT PowerFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::output_delay;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    PowerFilter(int nb_channels = 1);
    /// Destructor
    ~PowerFilter();

    /// Sets the memory of the AR1 (must be between 0 and 1)
    void set_memory(DataType_ memory_factor);
    /// gets the memory factor
    DataType_ get_memory() const;
    
  protected:
    virtual void process_impl(int64_t size) const override final;
    
  private:
    DataType_ memory_factor;
  };
}

#endif
