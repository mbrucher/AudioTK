/**
 * \file BesselFilter.h
 */

#ifndef ATK_EQ_BESSELFILTER_H
#define ATK_EQ_BESSELFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/EQ/EQInterface.h>

namespace ATK
{
  /// @brief Bessel coeffs for a low pass filter
  template<typename DataType_>
  class BesselLowPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public SingleCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using typename Parent::AlignedScalarVector;
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
    BesselLowPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency) override;
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const override;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) override;
    /// Gets the order of the filter
    unsigned int get_order() const override;
  };
  
  /// @brief Bessel coeffs for a high pass filter
  template<typename DataType_>
  class BesselHighPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public SingleCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
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
    BesselHighPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency) override;
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const override;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) override;
    /// Gets the order of the filter
    unsigned get_order() const override;
  };
  
  /// @brief Bessel coeffs for a band pass filter
  template<typename DataType_>
  class BesselBandPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public DualCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
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
    BesselBandPassCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies) override;
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1) override;
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const override;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) override;
    /// Gets the order of the filter
    unsigned get_order() const override;
  };
  
  /// @brief Bessel coeffs for a band stop filter
  template<typename DataType_>
  class BesselBandStopCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public DualCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
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
    BesselBandStopCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies) override;
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1) override;
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const override;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) override;
    /// Gets the order of the filter
    unsigned get_order() const override;
  };
}

#endif
