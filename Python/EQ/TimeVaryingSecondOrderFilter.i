
%{
#include <ATK/EQ/TimeVaryingSecondOrderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TimeVaryingBaseSecondOrderCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
  };
  
  template<class DataType>
  class TimeVaryingBandPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class TimeVaryingLowPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class TimeVaryingHighPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
  };
  
  template<class DataType>
  class TimeVaryingBandPassPeakCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
    void set_gain(DataType gain);
    DataType get_gain();
  };
  
  template<class DataType>
  class TimeVaryingAllPassCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class TimeVaryingLowShelvingCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class TimeVaryingHighShelvingCoefficients: public TimeVaryingBaseSecondOrderCoefficients<DataType>
  {
  public:
    void set_gain(DataType gain);
    DataType get_gain();
  };
}

%template(FloatTimeVaryingBaseSecondOrderCoefficients) ATK::TimeVaryingBaseSecondOrderCoefficients<float>;
%template(DoubleTimeVaryingBaseSecondOrderCoefficients) ATK::TimeVaryingBaseSecondOrderCoefficients<double>;

%template(FloatTimeVaryingBandPassCoefficients) ATK::TimeVaryingBandPassCoefficients<float>;
%template(DoubleTimeVaryingBandPassCoefficients) ATK::TimeVaryingBandPassCoefficients<double>;
%template(FloatTimeVaryingLowPassCoefficients) ATK::TimeVaryingLowPassCoefficients<float>;
%template(DoubleTimeVaryingLowPassCoefficients) ATK::TimeVaryingLowPassCoefficients<double>;
%template(FloatTimeVaryingHighPassCoefficients) ATK::TimeVaryingHighPassCoefficients<float>;
%template(DoubleTimeVaryingHighPassCoefficients) ATK::TimeVaryingHighPassCoefficients<double>;
%template(FloatTimeVaryingBandPassPeakCoefficients) ATK::TimeVaryingBandPassPeakCoefficients<float>;
%template(DoubleTimeVaryingBandPassPeakCoefficients) ATK::TimeVaryingBandPassPeakCoefficients<double>;
%template(FloatTimeVaryingAllPassCoefficients) ATK::TimeVaryingAllPassCoefficients<float>;
%template(DoubleTimeVaryingAllPassCoefficients) ATK::TimeVaryingAllPassCoefficients<double>;
%template(FloatTimeVaryingLowShelvingCoefficients) ATK::TimeVaryingLowShelvingCoefficients<float>;
%template(DoubleTimeVaryingLowShelvingCoefficients) ATK::TimeVaryingLowShelvingCoefficients<double>;
%template(FloatTimeVaryingHighShelvingCoefficients) ATK::TimeVaryingHighShelvingCoefficients<float>;
%template(DoubleTimeVaryingHighShelvingCoefficients) ATK::TimeVaryingHighShelvingCoefficients<double>;


%template(FloatTimeVaryingBandPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingBandPassCoefficients<float> >;
%template(DoubleTimeVaryingBandPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingBandPassCoefficients<double> >;
%template(FloatTimeVaryingLowPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingLowPassCoefficients<float> >;
%template(DoubleTimeVaryingLowPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingLowPassCoefficients<double> >;
%template(FloatTimeVaryingHighPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingHighPassCoefficients<float> >;
%template(DoubleTimeVaryingHighPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingHighPassCoefficients<double> >;
%template(FloatTimeVaryingBandPassPeakCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingBandPassPeakCoefficients<float> >;
%template(DoubleTimeVaryingBandPassPeakCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingBandPassPeakCoefficients<double> >;
%template(FloatTimeVaryingAllPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingAllPassCoefficients<float> >;
%template(DoubleTimeVaryingAllPassCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingAllPassCoefficients<double> >;
%template(FloatTimeVaryingLowShelvingCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingLowShelvingCoefficients<float> >;
%template(DoubleTimeVaryingLowShelvingCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingLowShelvingCoefficients<double> >;
%template(FloatTimeVaryingHighShelvingCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingHighShelvingCoefficients<float> >;
%template(DoubleTimeVaryingHighShelvingCoefficientsIIRFilter) ATK::TimeVaryingIIRFilter<ATK::TimeVaryingHighShelvingCoefficients<double> >;
