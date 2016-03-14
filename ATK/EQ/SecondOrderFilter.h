/**
 * \file SecondOrderFilter.h
 */

#ifndef ATK_EQ_SECONDORDERFILTER_H
#define ATK_EQ_SECONDORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Base class for all IIR second order filters
  template<typename DataType_>
  class SecondOrderBaseCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType cut_frequency;

    const static int in_order=2;
    const static int out_order=2;
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderBaseCoefficients(int nb_channels = 1);
    /// Sets the cut or central frequency of the filter
    void set_cut_frequency(DataType_ cut_frequency);
    /// Returns the cut or central frequency
    DataType_ get_cut_frequency() const;
  };

  /// Coefficients for a second order bandpass filter
  template<typename DataType_>
  class SecondOrderBandPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
    
  protected:
    void setup() override;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderBandPassCoefficients(int nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
     * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
     */
    void set_Q(DataType_ Q);
    /// Returns the Q factor
    DataType_ get_Q() const;
  };

  /// Coefficients for a second order lowpass filter
  template<typename DataType_>
  class SecondOrderLowPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
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
    SecondOrderLowPassCoefficients(int nb_channels = 1);
  };
  
  /// Coefficients for a second order highpass filter
  template<class DataType_>
  class SecondOrderHighPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
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
    SecondOrderHighPassCoefficients(int nb_channels = 1);
  };

  /// Coefficients for a second order bandpass peak filter
  template<typename DataType_>
  class SecondOrderBandPassPeakCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
    DataType gain;
  protected:
    void setup() override;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderBandPassPeakCoefficients(int nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(DataType_ Q);
    /// Returns the Q factor
    DataType_ get_Q() const;
    /// Sets the gain of the peak
    void set_gain(DataType_ gain);
    /// Returns the gain for the peak
    DataType_ get_gain() const;
  };

  
  /// Coefficients for a second order allpass filter
  template<typename DataType_>
  class SecondOrderAllPassCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
  protected:
    void setup() override;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderAllPassCoefficients(int nb_channels = 1);

    /// Sets the Q factor, must be strictly positive
    /*!
    * A smaller Q will lead to a bigger bandwidth, a bigger Q will lead to a smaller bandwidth
    */
    void set_Q(DataType_ Q);
    /// Returns the Q factor
    DataType_ get_Q() const;
  };

  /// Coefficients for a second order low-pass shelving filter
  template<typename DataType_>
  class SecondOrderLowShelvingCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  private:
    DataType gain;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderLowShelvingCoefficients(int nb_channels = 1);

    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;
  };
  
  /// Coefficients for a second order high-pass shelving filter
  template<typename DataType_>
  class SecondOrderHighShelvingCoefficients: public SecondOrderBaseCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef SecondOrderBaseCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup();
  private:
    DataType gain;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    SecondOrderHighShelvingCoefficients(int nb_channels = 1);

    /// Sets the gain of the shelf
    void set_gain(DataType_ gain);
    /// Returns the gain for the shelf
    DataType_ get_gain() const;
  };
}

#endif
