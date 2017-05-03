
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
  class SecondOrderSVFBaseCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class SecondOrderSVFLowPassCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class SecondOrderSVFBandPassCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class SecondOrderSVFHighPassCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class SecondOrderSVFNotchCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class SecondOrderSVFPeakCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  };
   
  template<class DataType>
  class SecondOrderSVFBellCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class SecondOrderSVFLowShelfCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class SecondOrderSVFHighShelfCoefficients: public SecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  ATKProperty(IIRFilter<SecondOrderSVFLowPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFLowPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFLowPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFLowPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFBandPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFBandPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFBandPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFBandPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFHighPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFHighPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFHighPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFHighPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFNotchCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFNotchCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFNotchCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFNotchCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFPeakCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFPeakCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFPeakCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFPeakCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFBellCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFLowShelfCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<SecondOrderSVFHighShelfCoefficients<double> >, gain, get_gain, set_gain);
}

%template(FloatSecondOrderSVFBaseCoefficients) ATK::SecondOrderSVFBaseCoefficients<float>;
%template(DoubleSecondOrderSVFBaseCoefficients) ATK::SecondOrderSVFBaseCoefficients<double>;

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
