
%{
#include <ATK/EQ/TimeVaryingSecondOrderSVFFilter.h>
%}

namespace ATK
{
  template<class Coefficients>
  class TimeVaryingSecondOrderSVFFilter: public Coefficients
  {
  public:
    TimeVaryingSecondOrderSVFFilter(int nb_channels=1);
    ~TimeVaryingSecondOrderSVFFilter();
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFBaseCoefficients: public BaseFilter
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFLowPassCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFBandPassCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFHighPassCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFNotchCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class TimeVaryingSecondOrderSVFPeakCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  };
   
  template<class DataType>
  class TimeVaryingSecondOrderSVFBellCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class TimeVaryingSecondOrderSVFLowShelfCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class TimeVaryingSecondOrderSVFHighShelfCoefficients: public TimeVaryingSecondOrderSVFBaseCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };
}

%template(FloatTimeVaryingSecondOrderSVFBaseCoefficients) ATK::TimeVaryingSecondOrderSVFBaseCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFBaseCoefficients) ATK::TimeVaryingSecondOrderSVFBaseCoefficients<double>;

%template(FloatTimeVaryingSecondOrderSVFLowPassCoefficients) ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFLowPassCoefficients) ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFBandPassCoefficients) ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFBandPassCoefficients) ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFHighPassCoefficients) ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFHighPassCoefficients) ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFNotchCoefficients) ATK::TimeVaryingSecondOrderSVFNotchCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFNotchCoefficients) ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFPeakCoefficients) ATK::TimeVaryingSecondOrderSVFPeakCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFPeakCoefficients) ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFBellCoefficients) ATK::TimeVaryingSecondOrderSVFBellCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFBellCoefficients) ATK::TimeVaryingSecondOrderSVFBellCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFLowShelfCoefficients) ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFLowShelfCoefficients) ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double>;
%template(FloatTimeVaryingSecondOrderSVFHighShelfCoefficients) ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<float>;
%template(DoubleTimeVaryingSecondOrderSVFHighShelfCoefficients) ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double>;

%template(FloatLowTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<float> >;
%template(DoubleLowTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowPassCoefficients<double> >;
%template(FloatBandTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<float> >;
%template(DoubleBandTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBandPassCoefficients<double> >;
%template(FloatHighTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<float> >;
%template(DoubleHighTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighPassCoefficients<double> >;
%template(FloatNotchTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<float> >;
%template(DoubleNotchTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFNotchCoefficients<double> >;
%template(FloatPeakTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<float> >;
%template(DoublePeakTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFPeakCoefficients<double> >;
%template(FloatBellTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<float> >;
%template(DoubleBellTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFBellCoefficients<double> >;
%template(FloatLowShelfTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<float> >;
%template(DoubleLowShelfTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFLowShelfCoefficients<double> >;
%template(FloatHighShelfTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<float> >;
%template(DoubleHighShelfTimeVaryingSecondOrderSVFFilter) ATK::TimeVaryingSecondOrderSVFFilter<ATK::TimeVaryingSecondOrderSVFHighShelfCoefficients<double> >;
