/**
 * \file LMSFilter.h
 * From Adaptive Filter Theory, Haykin
 */

#ifndef ATK_ADAPTIVE_LMSFILTER_H
#define ATK_ADAPTIVE_LMSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// LMS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT LMSFilter : public TypedBaseFilter<DataType_>
  {
    class LMSFilterImpl;
    std::unique_ptr<LMSFilterImpl> impl;
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;
    using Parent::input_delay;

  public:
    /**
     * @brief Creates the filter with a given size
     * @param size is the size of the underlying MA filter
     */
    LMSFilter(std::size_t size);
    /// Destructor
    ~LMSFilter();
    
    /// Changes the underlying size
    void set_size(std::size_t size);
    /// Retrieve the size
    std::size_t get_size() const;

    /// Sets the memory of the LMS algorithm
    void set_memory(DataType_ memory);
    /// Retrieves the memory
    DataType_ get_memory() const;
    /// Sets mu of the LMS algorithm
    void set_mu(DataType_ mu);
    /// Retrieves mu
    DataType_ get_mu() const;

    /// Retrieves w
    const DataType_* get_w() const;

  protected:
    virtual void process_impl(std::size_t size) const;
    
  private:
    std::size_t global_size;
  };
}

#endif
