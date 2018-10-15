/**
 * \file LMSFilter.h
 * From Adaptive Filter Theory, Haykin
 */

#ifndef ATK_ADAPTIVE_LMSFILTER_H
#define ATK_ADAPTIVE_LMSFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Adaptive/config.h>

namespace ATK
{
  /// LMS implementation as a filter
  template<typename DataType_>
  class ATK_ADAPTIVE_EXPORT LMSFilter final : public TypedBaseFilter<DataType_>
  {
    class LMSFilterImpl;
    std::unique_ptr<LMSFilterImpl> impl;
  protected:
    using Parent = TypedBaseFilter<DataType_>;
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
     * of the reference and the estimate.
     * @param size is the size of the underlying MA filter
     */
    LMSFilter(gsl::index size);
    /// Destructor
    ~LMSFilter() override;
    
    /// Changes the underlying size
    void set_size(gsl::index size);
    /// Retrieve the size
    gsl::index get_size() const;

    /// Sets the memory of the LMS algorithm
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;
    /// Sets mu of the LMS algorithm, should be less than 2/((size+1) * maximum of the DSP of the input signal)
    void set_mu(double mu);
    /// Retrieves mu
    double get_mu() const;

    /// Retrieves the coefficients
    const DataType_* get_w() const;
    /// Sets the coefficients
    void set_w(gsl::not_null<const DataType_*> w);

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

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;

  protected:
    void process_impl(gsl::index size) const final;
    bool learning;
    
  private:
    Mode mode;
  };

}

#endif
