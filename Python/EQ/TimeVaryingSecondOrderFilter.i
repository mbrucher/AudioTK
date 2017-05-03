
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

  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingBandPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighPassCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<TimeVaryingBandPassPeakCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingAllPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingLowShelvingCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<float> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<float> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<float> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<double> >, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<double> >, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<double> >, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(IIRFilter<TimeVaryingHighShelvingCoefficients<double> >, gain, get_gain, set_gain);
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
