
%{
#include <ATK/EQ/SecondOrderSVFFilter.h>
%}

namespace ATK
{
  template<class Coefficients>
  class SecondOrderSVFFilter: public Coefficients
  {
  public:
    SecondOrderSVFFilter();
    ~SecondOrderSVFFilter();
  };
  
  template<class DataType>
  class BaseSecondOrderSVFCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class LowSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class BandSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class HighSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class NotchSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class PeakSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  };
   
  template<class DataType>
  class BellSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class LowShelfSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class HighShelfSecondOrderSVFCoefficients: public BaseSecondOrderSVFCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };
}

%template(FloatBaseSecondOrderSVFCoefficients) ATK::BaseSecondOrderSVFCoefficients<float>;
%template(DoubleBaseSecondOrderSVFCoefficients) ATK::BaseSecondOrderSVFCoefficients<double>;

%template(FloatLowSecondOrderSVFCoefficients) ATK::LowSecondOrderSVFCoefficients<float>;
%template(DoubleLowSecondOrderSVFCoefficients) ATK::LowSecondOrderSVFCoefficients<double>;
%template(FloatBandSecondOrderSVFCoefficients) ATK::BandSecondOrderSVFCoefficients<float>;
%template(DoubleBandSecondOrderSVFCoefficients) ATK::BandSecondOrderSVFCoefficients<double>;
%template(FloatHighSecondOrderSVFCoefficients) ATK::HighSecondOrderSVFCoefficients<float>;
%template(DoubleHighSecondOrderSVFCoefficients) ATK::HighSecondOrderSVFCoefficients<double>;
%template(FloatNotchSecondOrderSVFCoefficients) ATK::NotchSecondOrderSVFCoefficients<float>;
%template(DoubleNotchSecondOrderSVFCoefficients) ATK::NotchSecondOrderSVFCoefficients<double>;
%template(FloatPeakSecondOrderSVFCoefficients) ATK::PeakSecondOrderSVFCoefficients<float>;
%template(DoublePeakSecondOrderSVFCoefficients) ATK::PeakSecondOrderSVFCoefficients<double>;
%template(FloatBellSecondOrderSVFCoefficients) ATK::BellSecondOrderSVFCoefficients<float>;
%template(DoubleBellSecondOrderSVFCoefficients) ATK::BellSecondOrderSVFCoefficients<double>;
%template(FloatLowShelfSecondOrderSVFCoefficients) ATK::LowShelfSecondOrderSVFCoefficients<float>;
%template(DoubleLowShelfSecondOrderSVFCoefficients) ATK::LowShelfSecondOrderSVFCoefficients<double>;
%template(FloatHighShelfSecondOrderSVFCoefficients) ATK::HighShelfSecondOrderSVFCoefficients<float>;
%template(DoubleHighShelfSecondOrderSVFCoefficients) ATK::HighShelfSecondOrderSVFCoefficients<double>;


%template(FloatLowSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::LowSecondOrderSVFCoefficients<float> >;
%template(DoubleLowSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::LowSecondOrderSVFCoefficients<double> >;
%template(FloatBandSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::BandSecondOrderSVFCoefficients<float> >;
%template(DoubleBandSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::BandSecondOrderSVFCoefficients<double> >;
%template(FloatHighSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::HighSecondOrderSVFCoefficients<float> >;
%template(DoubleHighSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::HighSecondOrderSVFCoefficients<double> >;
%template(FloatNotchSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::NotchSecondOrderSVFCoefficients<float> >;
%template(DoubleNotchSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::NotchSecondOrderSVFCoefficients<double> >;
%template(FloatPeakSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::PeakSecondOrderSVFCoefficients<float> >;
%template(DoublePeakSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::PeakSecondOrderSVFCoefficients<double> >;
%template(FloatBellSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::BellSecondOrderSVFCoefficients<float> >;
%template(DoubleBellSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::BellSecondOrderSVFCoefficients<double> >;
%template(FloatLowShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::LowShelfSecondOrderSVFCoefficients<float> >;
%template(DoubleLowShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::LowShelfSecondOrderSVFCoefficients<double> >;
%template(FloatHighShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::HighShelfSecondOrderSVFCoefficients<float> >;
%template(DoubleHighShelfSecondOrderSVFFilter) ATK::SecondOrderSVFFilter<ATK::HighShelfSecondOrderSVFCoefficients<double> >;
