
%{
#include <ATK/EQ/SecondOrderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class SecondOrderBaseCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };
  
  template<class DataType>
  class SecondOrderBandPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class SecondOrderLowPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class SecondOrderHighPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class SecondOrderBandPassPeakCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
    void set_gain(DataType gain);
    DataType get_gain();
  };
  
  template<class DataType>
  class SecondOrderAllPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class SecondOrderLowShelvingCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class SecondOrderHighShelvingCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };
}

%template(FloatSecondOrderBaseCoefficients) ATK::SecondOrderBaseCoefficients<float>;
%template(DoubleSecondOrderBaseCoefficients) ATK::SecondOrderBaseCoefficients<double>;

%template(FloatSecondOrderBandPassCoefficients) ATK::SecondOrderBandPassCoefficients<float>;
%template(DoubleSecondOrderBandPassCoefficients) ATK::SecondOrderBandPassCoefficients<double>;
%template(FloatSecondOrderLowPassCoefficients) ATK::SecondOrderLowPassCoefficients<float>;
%template(DoubleSecondOrderLowPassCoefficients) ATK::SecondOrderLowPassCoefficients<double>;
%template(FloatSecondOrderHighPassCoefficients) ATK::SecondOrderHighPassCoefficients<float>;
%template(DoubleSecondOrderHighPassCoefficients) ATK::SecondOrderHighPassCoefficients<double>;
%template(FloatSecondOrderBandPassPeakCoefficients) ATK::SecondOrderBandPassPeakCoefficients<float>;
%template(DoubleSecondOrderBandPassPeakCoefficients) ATK::SecondOrderBandPassPeakCoefficients<double>;
%template(FloatSecondOrderAllPassCoefficients) ATK::SecondOrderAllPassCoefficients<float>;
%template(DoubleSecondOrderAllPassCoefficients) ATK::SecondOrderAllPassCoefficients<double>;
%template(FloatSecondOrderLowShelvingCoefficients) ATK::SecondOrderLowShelvingCoefficients<float>;
%template(DoubleSecondOrderLowShelvingCoefficients) ATK::SecondOrderLowShelvingCoefficients<double>;
%template(FloatSecondOrderHighShelvingCoefficients) ATK::SecondOrderHighShelvingCoefficients<float>;
%template(DoubleSecondOrderHighShelvingCoefficients) ATK::SecondOrderHighShelvingCoefficients<double>;

%template(FloatSecondOrderBandPassFilter) ATK::IIRFilter<ATK::SecondOrderBandPassCoefficients<float> >;
%template(DoubleSecondOrderBandPassFilter) ATK::IIRFilter<ATK::SecondOrderBandPassCoefficients<double> >;
%template(FloatSecondOrderLowPassFilter) ATK::IIRFilter<ATK::SecondOrderLowPassCoefficients<float> >;
%template(DoubleSecondOrderLowPassFilter) ATK::IIRFilter<ATK::SecondOrderLowPassCoefficients<double> >;
%template(FloatSecondOrderHighPassFilter) ATK::IIRFilter<ATK::SecondOrderHighPassCoefficients<float> >;
%template(DoubleSecondOrderHighPassFilter) ATK::IIRFilter<ATK::SecondOrderHighPassCoefficients<double> >;
%template(FloatSecondOrderBandPassPeakFilter) ATK::IIRFilter<ATK::SecondOrderBandPassPeakCoefficients<float> >;
%template(DoubleSecondOrderBandPassPeakFilter) ATK::IIRFilter<ATK::SecondOrderBandPassPeakCoefficients<double> >;
%template(FloatSecondOrderAllPassFilter) ATK::IIRFilter<ATK::SecondOrderAllPassCoefficients<float> >;
%template(DoubleSecondOrderAllPassFilter) ATK::IIRFilter<ATK::SecondOrderAllPassCoefficients<double> >;
%template(FloatSecondOrderLowShelvingFilter) ATK::IIRFilter<ATK::SecondOrderLowShelvingCoefficients<float> >;
%template(DoubleSecondOrderLowShelvingFilter) ATK::IIRFilter<ATK::SecondOrderLowShelvingCoefficients<double> >;
%template(FloatSecondOrderHighShelvingFilter) ATK::IIRFilter<ATK::SecondOrderHighShelvingCoefficients<float> >;
%template(DoubleSecondOrderHighShelvingFilter) ATK::IIRFilter<ATK::SecondOrderHighShelvingCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderBandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderBandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderHighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderBandPassPeakCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderBandPassPeakCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderAllPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderAllPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderLowShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderLowShelvingCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderHighShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::SecondOrderHighShelvingCoefficients<double> >, double);
