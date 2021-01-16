 /**
 * \file Chebyshev1Filter.h
 */

#ifndef ATK_EQ_CHEBYSHEV1FILTER_H
#define ATK_EQ_CHEBYSHEV1FILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/EQ/EQInterface.h>

namespace ATK
{
  /// @brief Chebyshev 1 coeffs for a low pass filter
  template<typename DataType_>
  class Chebyshev1LowPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public SingleCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>, public RippleInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    CoeffDataType cut_frequency{0};
    /// Ripple of the filter
    CoeffDataType ripple{0};
    
    /// Order of the filter
    unsigned int in_order{1};
    /// Order of the filter
    unsigned int out_order{1};
    
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
    explicit Chebyshev1LowPassCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency) final;
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const final;
    /// Sets the ripple
    void set_ripple(CoeffDataType ripple) final;
    /// Gets the ripple
    CoeffDataType get_ripple() const final;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) final;
    /// Gets the order of the filter
    unsigned get_order() const final;
  };
  
  /// @brief Chebyshev 1 coeffs for a high pass filter
  template<typename DataType_>
  class Chebyshev1HighPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public SingleCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>, public RippleInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Cut-off of the filter
    CoeffDataType cut_frequency{0};
    /// Ripple of the filter
    CoeffDataType ripple{0};

    /// Order of the filter
    unsigned int in_order{1};
    /// Order of the filter
    unsigned int out_order{1};
    
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
    explicit Chebyshev1HighPassCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency) final;
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const final;
    /// Sets the ripple
    void set_ripple(CoeffDataType ripple) final;
    /// Gets the ripple
    CoeffDataType get_ripple() const final;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) final;
    /// Gets the order of the filter
    unsigned get_order() const final;
  };
  
  /// @brief Chebyshev 1 coeffs for a band pass filter
  template<typename DataType_>
  class Chebyshev1BandPassCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public RippleInterface<typename TypeTraits<DataType_>::Scalar>, public DualCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<CoeffDataType, CoeffDataType> cut_frequencies = {0, 0};
    /// Ripple of the filter
    CoeffDataType ripple{0};

    /// Order of the filter
    unsigned int in_order{1};
    /// Order of the filter
    unsigned int out_order{1};
    
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
    explicit Chebyshev1BandPassCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies) final;
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1) final;
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const final;
    /// Sets the ripple
    void set_ripple(CoeffDataType ripple) final;
    /// Gets the ripple
    CoeffDataType get_ripple() const final;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) final;
    /// Gets the order of the filter
    unsigned get_order() const final;

  };
  
  /// @brief Chebyshev 1 coeffs for a band stop filter
  template<typename DataType_>
  class Chebyshev1BandStopCoefficients: public TypedBaseFilter<DataType_>, public OrderInterface, public RippleInterface<typename TypeTraits<DataType_>::Scalar>, public DualCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Bandwidth of the filter
    std::pair<CoeffDataType, CoeffDataType> cut_frequencies = {0, 0};
    /// Ripple of the filter
    CoeffDataType ripple{0};

    /// Order of the filter
    unsigned int in_order{1};
    /// Order of the filter
    unsigned int out_order{1};
    
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
    explicit Chebyshev1BandStopCoefficients(gsl::index nb_channels = 1);

    /// Sets the bandwidth as a bandwidth
    void set_cut_frequencies(std::pair<CoeffDataType, CoeffDataType> cut_frequencies) final;
    /// Sets the bandwidth as two separate values
    void set_cut_frequencies(CoeffDataType f0, CoeffDataType f1) final;
    /// Gets the bandwidth
    std::pair<CoeffDataType, CoeffDataType> get_cut_frequencies() const final;
    /// Sets the ripple
    void set_ripple(CoeffDataType ripple) final;
    /// Gets the ripple
    CoeffDataType get_ripple() const final;
    /// Sets the order of the IIR filter
    void set_order(unsigned int order) final;
    /// Gets the order of the filter
    unsigned get_order() const final;
  };
}

#endif
