 /**
 * \file Chebyshev1Filter.h
 */

#ifndef ATK_EQ_CHEBYSHEV1FILTER_H
#define ATK_EQ_CHEBYSHEV1FILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// @brief Chebyshev 1 coeffs for a low pass filter
  template<typename DataType_>
  class Chebyshev1LowPassCoefficients: public TypedBaseFilter<DataType_>
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
    /// Ripple of the filter
    DataType ripple;
    
    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    Chebyshev1LowPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the ripple
    void set_ripple(DataType_ ripple);
    /// Gets the ripple
    DataType_ get_ripple() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };
  
  /// @brief Chebyshev 1 coeffs for a high pass filter
  template<typename DataType_>
  class Chebyshev1HighPassCoefficients: public TypedBaseFilter<DataType_>
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
    /// Ripple of the filter
    DataType ripple;

    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    Chebyshev1HighPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
    /// Sets the ripple
    void set_ripple(DataType_ ripple);
    /// Gets the ripple
    DataType_ get_ripple() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };
  
  /// @brief Chebyshev 1 coeffs for a band pass filter
  template<typename DataType_>
  class Chebyshev1BandPassCoefficients: public TypedBaseFilter<DataType_>
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
    /// Ripple of the filter
    DataType ripple;

    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    Chebyshev1BandPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    /// Gets the bandwidth
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the ripple
    void set_ripple(DataType_ ripple);
    /// Gets the ripple
    DataType_ get_ripple() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);    /// Gets the order of the filter
    unsigned get_order() const;

  };
  
  /// @brief Chebyshev 1 coeffs for a band stop filter
  template<typename DataType_>
  class Chebyshev1BandStopCoefficients: public TypedBaseFilter<DataType_>
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
    /// Ripple of the filter
    DataType ripple;

    /// Order of the filter
    unsigned int in_order;
    /// Order of the filter
    unsigned int out_order;
    
    void setup() override;
    
    /// Coefficients of the MA part of the IIR filter
    AlignedVector coefficients_in;
    /// Coefficients of the AR part of the IIR filter
    AlignedVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    Chebyshev1BandStopCoefficients(std::size_t nb_channels = 1);

    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<DataType_, DataType_> cut_frequencies);
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(DataType_ f0, DataType_ f1);
    /// Gets the bandwidth
    std::pair<DataType_, DataType_> get_cut_frequencies() const;
    /// Sets the ripple
    void set_ripple(DataType_ ripple);
    /// Gets the ripple
    DataType_ get_ripple() const;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order);
    /// Gets the order of the filter
    unsigned get_order() const;
  };
}

#endif
