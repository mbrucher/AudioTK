/**
 * \file BlockLMSFilter.h
 * From Adaptive Filter Theory, Haykin
 */

#ifndef ATK_ADAPTIVE_BLOCKLMSFILTER_H
#define ATK_ADAPTIVE_BLOCKLMSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /// LMS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT BlockLMSFilter final : public TypedBaseFilter<DataType_>
  {
    class BlockLMSFilterImpl;
    std::unique_ptr<BlockLMSFilterImpl> impl;
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
     * An LMS filter is an adaptive filter that tries to match its second input with a linear combination of the first input, outputing the difference 
     * of the reference and the estimate.
     * @param size is the size of the underlying MA filter
     */
    BlockLMSFilter(std::size_t size);
    /// Destructor
    ~BlockLMSFilter();
    
    /// Changes the underlying size
    void set_size(std::size_t size);
    /// Retrieve the size
    std::size_t get_size() const;

    /// Sets the memory of the LMS algorithm
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;
    /// Sets mu of the LMS algorithm, should be less than 2/((size+1) * maximum of the DSP of the input signal)
    void set_mu(double mu);
    /// Retrieves mu
    double get_mu() const;

    /// Retrieves w
    const DataType_* get_w() const;

    enum class Mode
    {
      NORMAL,
      NORMALIZED,
      SIGNERROR,
      SIGNDATA,
      SIGNSIGN
    };

    /// Sets the way the filter is updated
    void set_mode(Mode mode);
    /// Retrieves the way the filter is updated
    Mode get_mode() const;

  protected:
    virtual void process_impl(std::size_t size) const;
    
  private:
    Mode mode;
    std::size_t global_size;
  };
}

#endif
