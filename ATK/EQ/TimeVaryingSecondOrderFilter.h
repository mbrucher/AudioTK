/**
 * \file TimeVaryingSecondOrderFilter.h
 */

#ifndef ATK_EQ_TIMEVARYINGSECONDORDERFILTER_H
#define ATK_EQ_TIMEVARYINGSECONDORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class TimeVaryingBaseSecondOrderCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:

    const static int in_order=2;
    const static int out_order=2;
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;

    double min_frequency;
    double max_frequency;
    double memory;
    int number_of_steps;

    void setup() override;

  public:
    TimeVaryingBaseSecondOrderCoefficients();

    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_memory(double memory);
    double get_memory() const;
  };

  /**
   * Coefficients for a second order bandpass filter
   */
  template<typename DataType_>
  class TimeVaryingBandPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
    
  protected:
    void setup() override;
    
  public:
    TimeVaryingBandPassCoefficients();

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  /**
   * Coefficients for a second order lowpass filter
   */
  template<typename DataType_>
  class TimeVaryingLowPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  public:
    TimeVaryingLowPassCoefficients();
  };
  
  /**
   * Coefficients for a second order highpass filter
   */
  template<class DataType_>
  class TimeVaryingHighPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  public:
    TimeVaryingHighPassCoefficients();
  };

  /**
   * Coefficients for a second order bandpass peak filter
   */
  template<typename DataType_>
  class TimeVaryingBandPassPeakCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
    DataType gain;
  protected:
    void setup() override;
    
  public:
    TimeVaryingBandPassPeakCoefficients();

    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
    void set_gain(DataType_ gain);
    DataType_ get_gain() const;
  };

  
  /**
   * Coefficients for a second order allpass filter
   */
  template<typename DataType_>
  class TimeVaryingAllPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
  private:
    DataType Q;
  protected:
    void setup() override;
    
  public:
    TimeVaryingAllPassCoefficients();

    /// Q is the allpass relative width (to the sampling rate)
    void set_Q(DataType_ Q);
    DataType_ get_Q() const;
  };

  /**
   * Coefficients for a second order low-pass shelving filter
   */
  template<typename DataType_>
  class TimeVaryingLowShelvingCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  private:
    DataType gain;
    
  public:
    TimeVaryingLowShelvingCoefficients();

    void set_gain(DataType_ gain);
    DataType_ get_gain() const;
  };
  
  /**
   * Coefficients for a second order high-pass shelving filter
   */
  template<typename DataType_>
  class TimeVaryingHighShelvingCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef TimeVaryingBaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::min_frequency;
    using Parent::max_frequency;
    using Parent::number_of_steps;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    void setup() override;
  private:
    DataType gain;
    
  public:
    TimeVaryingHighShelvingCoefficients();

    void set_gain(DataType_ gain);
    DataType_ get_gain() const;
  };
}

#endif
