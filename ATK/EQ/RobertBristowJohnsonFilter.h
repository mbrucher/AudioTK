/**
 * \file RobertBristowJohnsonFilter.h
 */

#ifndef ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H
#define ATK_EQ_ROBERTBRISTOWJOHNSONFILTER_H

#include <ATK/EQ/SecondOrderFilter.h>
#include <ATK/EQ/EQInterface.h>

namespace ATK
{
  /// RBJ low pass filter
  template<typename DataType_>
  class RobertBristowJohnsonLowPassCoefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;
        
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonLowPassCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a stronger attenuation, a bigger Q will lead to a stronger enhancement
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ high pass filter
  template<typename DataType_>
  class RobertBristowJohnsonHighPassCoefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonHighPassCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a stronger attenuation, a bigger Q will lead to a stronger enhancement
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ band pass filter
  template<typename DataType_>
  class RobertBristowJohnsonBandPassCoefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonBandPassCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ band pass filter
  template<typename DataType_>
  class RobertBristowJohnsonBandPass2Coefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonBandPass2Coefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ band stop filter
  template<typename DataType_>
  class RobertBristowJohnsonBandStopCoefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonBandStopCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ all pass filter
  template<typename DataType_>
  class RobertBristowJohnsonAllPassCoefficients : public SecondOrderBaseCoefficients<DataType_>, public QInterface<typename TypeTraits<DataType_>::Scalar>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonAllPassCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a spread response, a bigger Q will lead to a smaller response
     */
    void set_Q(CoeffDataType Q) final;
    /// Returns the Q factor
    CoeffDataType get_Q() const final;
  };

  /// RBJ band peak filter
  template<typename DataType_>
  class RobertBristowJohnsonBandPassPeakCoefficients : public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;
    CoeffDataType gain;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonBandPassPeakCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a spread response, a bigger Q will lead to a smaller response
     */
    void set_Q(CoeffDataType Q);
    /// Returns the Q factor
    CoeffDataType get_Q() const;
    /// Sets the gain of the peak
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the peak
    CoeffDataType get_gain() const;
  };

  /// RBJ low shelf filter
  template<typename DataType_>
  class RobertBristowJohnsonLowShelvingCoefficients : public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;
    CoeffDataType gain;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonLowShelvingCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a spread response, a bigger Q will lead to a smaller response
     */
    void set_Q(CoeffDataType Q);
    /// Returns the Q factor
    CoeffDataType get_Q() const;
    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;
};

  /// RBJ high shelf filter
  template<typename DataType_>
  class RobertBristowJohnsonHighShelvingCoefficients : public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using typename Parent::CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    CoeffDataType Q;
    CoeffDataType gain;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RobertBristowJohnsonHighShelvingCoefficients(std::size_t nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a spread response, a bigger Q will lead to a smaller response
     */
    void set_Q(CoeffDataType Q);
    /// Returns the Q factor
    CoeffDataType get_Q() const;
    /// Sets the gain of the shelf
    void set_gain(CoeffDataType gain);
    /// Returns the gain for the shelf
    CoeffDataType get_gain() const;
  };
}

#endif
