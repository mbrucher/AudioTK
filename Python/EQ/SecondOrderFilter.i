
%{
#include <ATK/EQ/SecondOrderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class BaseSecondOrderCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };
  
  template<class DataType>
  class BandPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class LowPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class HighPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class BandPassPeakCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
    void set_gain(DataType gain);
    DataType get_gain();
  };
  
  template<class DataType>
  class AllPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class LowShelvingCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class HighShelvingCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };
}

%template(FloatBaseSecondOrderCoefficients) ATK::BaseSecondOrderCoefficients<float>;
%template(DoubleBaseSecondOrderCoefficients) ATK::BaseSecondOrderCoefficients<double>;

%template(FloatBandPassCoefficients) ATK::BandPassCoefficients<float>;
%template(DoubleBandPassCoefficients) ATK::BandPassCoefficients<double>;
%template(FloatLowPassCoefficients) ATK::LowPassCoefficients<float>;
%template(DoubleLowPassCoefficients) ATK::LowPassCoefficients<double>;
%template(FloatHighPassCoefficients) ATK::HighPassCoefficients<float>;
%template(DoubleHighPassCoefficients) ATK::HighPassCoefficients<double>;
%template(FloatBandPassPeakCoefficients) ATK::BandPassPeakCoefficients<float>;
%template(DoubleBandPassPeakCoefficients) ATK::BandPassPeakCoefficients<double>;
%template(FloatAllPassCoefficients) ATK::AllPassCoefficients<float>;
%template(DoubleAllPassCoefficients) ATK::AllPassCoefficients<double>;
%template(FloatLowShelvingCoefficients) ATK::LowShelvingCoefficients<float>;
%template(DoubleLowShelvingCoefficients) ATK::LowShelvingCoefficients<double>;
%template(FloatHighShelvingCoefficients) ATK::HighShelvingCoefficients<float>;
%template(DoubleHighShelvingCoefficients) ATK::HighShelvingCoefficients<double>;


%template(FloatBandPassFilter) ATK::IIRFilter<ATK::BandPassCoefficients<float> >;
%template(DoubleBandPassFilter) ATK::IIRFilter<ATK::BandPassCoefficients<double> >;
%template(FloatLowPassFilter) ATK::IIRFilter<ATK::LowPassCoefficients<float> >;
%template(DoubleLowPassFilter) ATK::IIRFilter<ATK::LowPassCoefficients<double> >;
%template(FloatHighPassFilter) ATK::IIRFilter<ATK::HighPassCoefficients<float> >;
%template(DoubleHighPassFilter) ATK::IIRFilter<ATK::HighPassCoefficients<double> >;
%template(FloatBandPassPeakFilter) ATK::IIRFilter<ATK::BandPassPeakCoefficients<float> >;
%template(DoubleBandPassPeakFilter) ATK::IIRFilter<ATK::BandPassPeakCoefficients<double> >;
%template(FloatAllPassFilter) ATK::IIRFilter<ATK::AllPassCoefficients<float> >;
%template(DoubleAllPassFilter) ATK::IIRFilter<ATK::AllPassCoefficients<double> >;
%template(FloatLowShelvingFilter) ATK::IIRFilter<ATK::LowShelvingCoefficients<float> >;
%template(DoubleLowShelvingFilter) ATK::IIRFilter<ATK::LowShelvingCoefficients<double> >;
%template(FloatHighShelvingFilter) ATK::IIRFilter<ATK::HighShelvingCoefficients<float> >;
%template(DoubleHighShelvingFilter) ATK::IIRFilter<ATK::HighShelvingCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::BandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::LowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::HighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::HighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::BandPassPeakCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BandPassPeakCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::AllPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::AllPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::LowShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LowShelvingCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::HighShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::HighShelvingCoefficients<double> >, double);
