
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
%template(FloatLowShelvingCoefficients) ATK::LowShelvingCoefficients<float>;
%template(DoubleLowShelvingCoefficients) ATK::LowShelvingCoefficients<double>;
%template(FloatHighShelvingCoefficients) ATK::HighShelvingCoefficients<float>;
%template(DoubleHighShelvingCoefficients) ATK::HighShelvingCoefficients<double>;


%template(FloatBandPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::BandPassCoefficients<float> >;
%template(DoubleBandPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::BandPassCoefficients<double> >;
%template(FloatLowPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowPassCoefficients<float> >;
%template(DoubleLowPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowPassCoefficients<double> >;
%template(FloatHighPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighPassCoefficients<float> >;
%template(DoubleHighPassCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighPassCoefficients<double> >;
%template(FloatBandPassPeakCoefficientsIIRFilter) ATK::IIRFilter<ATK::BandPassPeakCoefficients<float> >;
%template(DoubleBandPassPeakCoefficientsIIRFilter) ATK::IIRFilter<ATK::BandPassPeakCoefficients<double> >;
%template(FloatLowShelvingCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowShelvingCoefficients<float> >;
%template(DoubleLowShelvingCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowShelvingCoefficients<double> >;
%template(FloatHighShelvingCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighShelvingCoefficients<float> >;
%template(DoubleHighShelvingCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighShelvingCoefficients<double> >;
