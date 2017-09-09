/**
 * \file ButterworthFilter.h
 */

#ifndef ATK_EQ_BUTTERWORTHFILTER_H
#define ATK_EQ_BUTTERWORTHFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// @brief Butterworth coeffs for a low pass filter
  template<typename DataType_>
  class ButterworthLowPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    CoeffDataType cut_frequency;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedScalarVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthLowPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency);
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };

  /// @brief Butterworth coeffs for a high pass filter
  template<typename DataType_>
  class ButterworthHighPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    CoeffDataType cut_frequency;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedScalarVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthHighPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency);
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };

  /// @brief Butterworth coeffs for a band pass filter
  template<typename DataType_>
  class ButterworthBandPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<CoeffDataType, CoeffDataType> cut_frequencies;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedScalarVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1);
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };
  
  /// @brief Butterworth coeffs for a band stop filter
  template<typename DataType_>
  class ButterworthBandStopCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<CoeffDataType, CoeffDataType> cut_frequencies;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedScalarVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandStopCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1);
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };
}

#endif
