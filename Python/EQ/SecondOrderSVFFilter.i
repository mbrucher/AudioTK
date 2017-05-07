
%{
#include <ATK/EQ/SecondOrderSVFFilter.h>
%}

namespace ATK
{
  template<class Coefficients>
  class SecondOrderSVFFilter: public Coefficients
  {
  public:
    SecondOrderSVFFilter(int nb_channels=1);
    ~SecondOrderSVFFilter();
  };
  
  template<class DataType>
  class SecondOrderSVFLowPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class SecondOrderSVFBandPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class SecondOrderSVFHighPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class SecondOrderSVFNotchCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class SecondOrderSVFPeakCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
   
  template<class DataType>
  class SecondOrderSVFBellCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class SecondOrderSVFLowShelfCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class SecondOrderSVFHighShelfCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType gain);
    DataType get_gain();
  };

  ATKProperty(SecondOrderSVFLowPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFLowPassCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFLowPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFLowPassCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFBandPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFBandPassCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFBandPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFBandPassCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFHighPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFHighPassCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFHighPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFHighPassCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFNotchCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFNotchCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFNotchCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFNotchCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFPeakCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFPeakCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFPeakCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFPeakCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFBellCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFBellCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFBellCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(SecondOrderSVFBellCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFBellCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFBellCoefficients<double>, gain, get_gain, set_gain);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFLowShelfCoefficients<double>, gain, get_gain, set_gain);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(SecondOrderSVFHighShelfCoefficients<double>, gain, get_gain, set_gain);
}

%template(FloatSecondOrderSVFLowPassCoefficients) ATK::SecondOrderSVFLowPassCoefficients<float>;
%template(DoubleSecondOrderSVFLowPassCoefficients) ATK::SecondOrderSVFLowPassCoefficients<double>;
%template(FloatSecondOrderSVFBandPassCoefficients) ATK::SecondOrderSVFBandPassCoefficients<float>;
%template(DoubleSecondOrderSVFBandPassCoefficients) ATK::SecondOrderSVFBandPassCoefficients<double>;
%template(FloatSecondOrderSVFHighPassCoefficients) ATK::SecondOrderSVFHighPassCoefficients<float>;
%template(DoubleSecondOrderSVFHighPassCoefficients) ATK::SecondOrderSVFHighPassCoefficients<double>;
%template(FloatSecondOrderSVFNotchCoefficients) ATK::SecondOrderSVFNotchCoefficients<float>;
%template(DoubleSecondOrderSVFNotchCoefficients) ATK::SecondOrderSVFNotchCoefficients<double>;
%template(FloatSecondOrderSVFPeakCoefficients) ATK::SecondOrderSVFPeakCoefficients<float>;
%template(DoubleSecondOrderSVFPeakCoefficients) ATK::SecondOrderSVFPeakCoefficients<double>;
%template(FloatSecondOrderSVFBellCoefficients) ATK::SecondOrderSVFBellCoefficients<float>;
%template(DoubleSecondOrderSVFBellCoefficients) ATK::SecondOrderSVFBellCoefficients<double>;
%template(FloatSecondOrderSVFLowShelfCoefficients) ATK::SecondOrderSVFLowShelfCoefficients<float>;
%template(DoubleSecondOrderSVFLowShelfCoefficients) ATK::SecondOrderSVFLowShelfCoefficients<double>;
%template(FloatSecondOrderSVFHighShelfCoefficients) ATK::SecondOrderSVFHighShelfCoefficients<float>;
%template(DoubleSecondOrderSVFHighShelfCoefficients) ATK::SecondOrderSVFHighShelfCoefficients<double>;


%template(FloatLowSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFLowPassCoefficients<float> >;
%template(DoubleLowSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFLowPassCoefficients<double> >;
%template(FloatBandSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFBandPassCoefficients<float> >;
%template(DoubleBandSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFBandPassCoefficients<double> >;
%template(FloatHighSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFHighPassCoefficients<float> >;
%template(DoubleHighSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFHighPassCoefficients<double> >;
%template(FloatNotchSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFNotchCoefficients<float> >;
%template(DoubleNotchSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFNotchCoefficients<double> >;
%template(FloatPeakSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFPeakCoefficients<float> >;
%template(DoublePeakSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFPeakCoefficients<double> >;
%template(FloatBellSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFBellCoefficients<float> >;
%template(DoubleBellSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFBellCoefficients<double> >;
%template(FloatLowShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFLowShelfCoefficients<float> >;
%template(DoubleLowShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFLowShelfCoefficients<double> >;
%template(FloatHighShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFHighShelfCoefficients<float> >;
%template(DoubleHighShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::SecondOrderSVFHighShelfCoefficients<double> >;
