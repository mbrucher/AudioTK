/**
 * \file ConvolutionFilter.h
 */

#ifndef ATK_SPECIAL_CONVOLUTIONFILTER_H
#define ATK_SPECIAL_CONVOLUTIONFILTER_H

#include <ATK/Special/config.h>
#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/Utility/FFT.h>

#include <list>
#include <vector>

namespace ATK
{
  /// A zero-delay convolution filter based on FFT
  template<typename DataType_>
  class ATK_SPECIAL_EXPORT ConvolutionFilter final : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::DataType;
    using typename Parent::AlignedVector;
    using typename Parent::AlignedScalarVector;
    using Parent::setup;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::input_delay;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

    using AlignedComplexVector = typename TypedBaseFilter<std::complex<DataType_> >::AlignedVector;
  protected:
    /// Current amount of data in the buffer
    mutable unsigned int split_position{0};
    /// Size of the individual FFTs that are processed
    unsigned int split_size = 0;
    
    /// FFT object for fast FFT/iFFT
    FFT<DataType> processor;
    
    /// Impulse convolved with the input signal
    AlignedScalarVector impulse;
    /// This buffer contains the head of the last convolution (easier to have 2 parts)
    mutable AlignedVector temp_out_buffer;
    /// Called partial convolutions, but actually contains the former temp_in_buffers
    mutable std::list<AlignedComplexVector> partial_frequency_input;
    /// Copied so that it's not reallocated each time
    mutable AlignedComplexVector result;

    /// The impulse is stored here in a unique vector, split in split_size FFTs, one after the other
    AlignedComplexVector partial_frequency_impulse;

    /// Compute the partial convolutions
    void compute_convolutions() const;
    /// Create a new chunk and compute the convolution
    void process_new_chunk(int64_t position) const;

    /// Process the first split_size elements of the convolution
    void process_impulse_beginning(int64_t processed_size, unsigned int position) const;

  public:
    /// Build a new convolution filter
    ConvolutionFilter();

    /**
     * @brief Set the impulse for the convolution
     * @param impulse is the impulse for the convolution
     */
    void set_impulse(AlignedScalarVector impulse);
    
    /*!
    * @brief Set the split size
    * @param split_size is the size of the individual FFTs
    */
    void set_split_size(unsigned int split_size);
  protected:
    void process_impl(gsl::index size) const final;
    
    void setup() final;
    
  };
}

#endif
