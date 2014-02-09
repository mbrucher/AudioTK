/**
 * \file SecondOrderFilter.h
 */

#ifndef ATK_EQ_SECONDORDERFILTER_H
#define ATK_EQ_SECONDORDERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class BaseCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    DataType cut_frequency;
    
  public:
    BaseCoefficients();
    void set_cut_frequency(DataType cut_frequency);
  };

  /**
   * Coefficients for a second order bandpass filter
   */
  template<typename DataType_>
  class BandPassCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    DataType Q;
    
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    
  public:
    void set_Q(DataType Q);
  };
  
  /**
   * Coefficients for a second order lowpass filter
   */
  template<typename DataType_>
  class LowPassCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
  };
  
  /**
   * Coefficients for a second order highpass filter
   */
  template<class DataType_>
  class HighPassCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
  };
  
  /**
   * Coefficients for a second order allpass peak filter
   */
  template<typename DataType_>
  class BandPassPeakCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    DataType Q;
    
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_Q(DataType Q);
    void set_gain(DataType gain);
  };
  
  /**
   * Coefficients for a second order lowpass filter
   */
  template<typename DataType_>
  class LowShelvingCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_gain(DataType gain);
  };
  
  /**
   * Coefficients for a second order high pass shelving filter
   */
  template<typename DataType_>
  class HighShelvingCoefficients: public BaseCoefficients<DataType_>
  {
  public:
    typedef BaseCoefficients<DataType_> Parent;
    typedef DataType_ DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
  private:
    void setup();
    
  protected:
    DataType coefficients_in[3];
    DataType coefficients_out[2];
    DataType gain;
    
  public:
    void set_gain(DataType gain);
  };
  
  /**
   * Second order filter template class
   */
  template<class Coefficients >
  class SecondOrderFilter: public Coefficients
  {
  public:
    typedef Coefficients Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::coefficients_in;
    using Parent::coefficients_out;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;

  private:
    DataType buffer_in[2];
    DataType buffer_out[2];
    
  public:
    SecondOrderFilter();
    
    virtual void process_impl(int size);
  };
}

#endif
