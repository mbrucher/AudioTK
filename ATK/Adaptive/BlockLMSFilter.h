/**
 * \file BlockLMSFilter.h
 * From Adaptive Filter Theory, Haykin
 */

#ifndef ATK_ADAPTIVE_BLOCKLMSFILTER_H
#define ATK_ADAPTIVE_BLOCKLMSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Adaptive/config.h>

namespace ATK
{
  /// LMS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT BlockLMSFilter final : public TypedBaseFilter<DataType_>
  {
    class BlockLMSFilterImpl;
    std::unique_ptr<BlockLMSFilterImpl> impl;
  protected:
    /// Parent class of the filter
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
     * An LMS filter is an adaptive filter that tries to match its second input with a linear combination of the first input, outputting the difference 
     * of the reference and the estimate. The block variant only updates the coefficients each time a block is processed.
     * @param size is the size of the underlying MA filter
     */
    BlockLMSFilter(gsl::index size);
    /// Destructor
    ~BlockLMSFilter() override;
    
    /// Changes the underlying size
    void set_size(gsl::index size);
    /// Retrieve the size
    gsl::index get_size() const;
    /// Changes the block size
    void set_block_size(gsl::index size);
    /// Retrieve the block size
    gsl::index get_block_size() const;

    /// Sets the memory of the LMS algorithm
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;
    /// Sets mu of the LMS algorithm, should be less than 2/((size+1) * maximum of the DSP of the input signal)
    void set_mu(double mu);
    /// Retrieves mu
    double get_mu() const;

    /// Retrieves the coefficients
    const std::complex<double>* get_w() const;
    /// Sets the coefficients
    void set_w(gsl::not_null<const std::complex<double>*> w);

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;

  protected:
    void process_impl(gsl::index size) const final;
  };
}

#endif
