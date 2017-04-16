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
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    DataType cut_frequency;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthLowPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };

  /// @brief Butterworth coeffs for a high pass filter
  template<typename DataType_>
  class ButterworthHighPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    DataType cut_frequency;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthHighPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };

  /// @brief Butterworth coeffs for a band pass filter
  template<typename DataType_>
  class ButterworthBandPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<DataType, DataType> cut_frequencies;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandPassCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    /// Gets the bandwidth
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
  
  /// @brief Butterworth coeffs for a band stop filter
  template<typename DataType_>
  class ButterworthBandStopCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedVector;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<DataType, DataType> cut_frequencies;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    AlignedVector coefficients_in;
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ButterworthBandStopCoefficients(unsigned int nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    /// Gets the bandwidth
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
  };
}

#endif
