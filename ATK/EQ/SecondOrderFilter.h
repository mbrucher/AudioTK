/**
 * \file SecondOrderFilter.h
 */

#ifndef ATK_EQ_SECONDORDERFILTER_H
#define ATK_EQ_SECONDORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class BaseSecondOrderCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType cut_frequency;

    const static int in_order=2;
    const static int out_order=2;
    
  public:
    BaseSecondOrderCoefficients();
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
  };

  /**
   * Coefficients for a second order bandpass filter
   */
  template<typename DataType_>
  class BandPassCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    DataType Q;
    
  protected:
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  /**
   * Coefficients for a second order lowpass filter
   */
  template<typename DataType_>
  class LowPassCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
  };
  
  /**
   * Coefficients for a second order highpass filter
   */
  template<class DataType_>
  class HighPassCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
  };
  
  /**
   * Coefficients for a second order allpass peak filter
   */
  template<typename DataType_>
  class BandPassPeakCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    DataType Q;
    
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType gain);
    DataType get_gain() const;
  };
  
  /**
   * Coefficients for a second order lowpass filter
   */
  template<typename DataType_>
  class LowShelvingCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_gain(DataType gain);
    DataType get_gain() const;
  };
  
  /**
   * Coefficients for a second order high pass shelving filter
   */
  template<typename DataType_>
  class HighShelvingCoefficients: public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    void setup();
    
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_gain(DataType gain);
    DataType get_gain() const;
  };
}

#endif
