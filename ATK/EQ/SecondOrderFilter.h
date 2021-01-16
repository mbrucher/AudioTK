/**
 * \file SecondOrderFilter.h
 */

#ifndef ATK_EQ_SECONDORDERFILTER_H
#define ATK_EQ_SECONDORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>
#include <ATK/EQ/EQInterface.h>

namespace ATK
{
  /// Base class for all IIR second order filters
  template<typename DataType_>
  class SecondOrderCoreCoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::setup;
  protected:
    constexpr static gsl::index in_order = 2;
    constexpr static gsl::index out_order = 2;
    AlignedScalarVector coefficients_in;
    AlignedScalarVector coefficients_out;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    */
    explicit SecondOrderCoreCoefficients(gsl::index nb_channels = 1);
  };
  
  /// Base class for all IIR second order filters
  template<typename DataType_>
  class SecondOrderBaseCoefficients : public SecondOrderCoreCoefficients<DataType_>, public SingleCutFrequencyInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderCoreCoefficients<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::setup;
  protected:
    CoeffDataType cut_frequency{0};

    constexpr static gsl::index in_order = 2;
    constexpr static gsl::index out_order = 2;
    AlignedScalarVector coefficients_in;
    AlignedScalarVector coefficients_out;

    explicit SecondOrderBaseCoefficients(gsl::index nb_channels);
    void setup() override;
  public:
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(CoeffDataType cut_frequency) final;
    /// Returns the cut or central frequency
    CoeffDataType get_cut_frequency() const final;
  };

  /// Coefficients for a second order bandpass filter
  template<typename DataType_>
  class SecondOrderBandPassCoefficients: public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    CoeffDataType Q{1};
    
  protected:
    void setup() override;
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderBandPassCoefficients(gsl::index nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// Coefficients for a second order lowpass filter
  template<typename DataType_>
  class SecondOrderLowPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderLowPassCoefficients(gsl::index nb_channels = 1);
  };
  
  /// Coefficients for a second order highpass filter
  template<class DataType_>
  class SecondOrderHighPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderHighPassCoefficients(gsl::index nb_channels = 1);
  };

  /// Coefficients for a second order bandpass peak filter
  template<typename DataType_>
  class SecondOrderBandPassPeakCoefficients: public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>, public GainInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    CoeffDataType Q{1};
    CoeffDataType gain{1};
  protected:
    void setup() override;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderBandPassPeakCoefficients(gsl::index nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
    /// Sets the gain of the peak
    void set_gain(CoeffDataType gain) final;
    /// Returns the gain for the peak
    CoeffDataType get_gain() const final;
  };

  
  /// Coefficients for a second order allpass filter
  template<typename DataType_>
  class SecondOrderAllPassCoefficients: public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    CoeffDataType Q{1};
  protected:
    void setup() override;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderAllPassCoefficients(gsl::index nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// Coefficients for a second order low-pass shelving filter
  template<typename DataType_>
  class SecondOrderLowShelvingCoefficients: public SecondOrderBaseCoefficients<DataType_>, public GainInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  private:
    CoeffDataType gain{1};
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderLowShelvingCoefficients(gsl::index nb_channels = 1);

    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain) final;
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const final;
  };
  
  /// Coefficients for a second order high-pass shelving filter
  template<typename DataType_>
  class SecondOrderHighShelvingCoefficients: public SecondOrderBaseCoefficients<DataType_>, public GainInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderBaseCoefficients<DataType_>;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  private:
    CoeffDataType gain{1};
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SecondOrderHighShelvingCoefficients(gsl::index nb_channels = 1);

    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain) final;
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const final;
  };
}

#endif
