
%{
#include <ATK/EQ/TimeVaryingSecondOrderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TimeVaryingBandPassCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class TimeVaryingLowPassCoefficients: public BaseFilter
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
  class TimeVaryingHighPassCoefficients: public BaseFilter
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
  class TimeVaryingBandPassPeakCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_Q(DataType Q);
    DataType get_Q();
    void set_gain(DataType gain);
    DataType get_gain();
  };
  
  template<class DataType>
  class TimeVaryingAllPassCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_Q(DataType Q);
    DataType get_Q();
  };
  
  template<class DataType>
  class TimeVaryingLowShelvingCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_gain(DataType gain);
    DataType get_gain();
  };

  template<class DataType>
  class TimeVaryingHighShelvingCoefficients: public BaseFilter
  {
  public:
    void set_min_frequency(double min_frequency);
    double get_min_frequency() const;
    void set_max_frequency(double max_frequency);
    double get_max_frequency() const;
    void set_number_of_steps(int number_of_steps);
    int get_number_of_steps() const;
    void set_gain(DataType gain);
    DataType get_gain();
  };

  ATKProperty(TimeVaryingBandPassCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingBandPassCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingBandPassCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingBandPassCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingBandPassCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingBandPassCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingBandPassCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingBandPassCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingLowPassCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingLowPassCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingLowPassCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingLowPassCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingLowPassCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingLowPassCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingHighPassCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingHighPassCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingHighPassCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingHighPassCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingHighPassCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingHighPassCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingBandPassPeakCoefficients<double>, gain, get_gain, set_gain);
  ATKProperty(TimeVaryingAllPassCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingAllPassCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingAllPassCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingAllPassCoefficients<float>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingAllPassCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingAllPassCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingAllPassCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingAllPassCoefficients<double>, Q, get_Q, set_Q);
  ATKProperty(TimeVaryingLowShelvingCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingLowShelvingCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingLowShelvingCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingLowShelvingCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(TimeVaryingLowShelvingCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingLowShelvingCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingLowShelvingCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingLowShelvingCoefficients<double>, gain, get_gain, set_gain);
  ATKProperty(TimeVaryingHighShelvingCoefficients<float>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingHighShelvingCoefficients<float>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingHighShelvingCoefficients<float>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingHighShelvingCoefficients<float>, gain, get_gain, set_gain);
  ATKProperty(TimeVaryingHighShelvingCoefficients<double>, min_frequency, get_min_frequency, set_min_frequency);
  ATKProperty(TimeVaryingHighShelvingCoefficients<double>, max_frequency, get_max_frequency, set_max_frequency);
  ATKProperty(TimeVaryingHighShelvingCoefficients<double>, number_of_steps, get_number_of_steps, set_number_of_steps);
  ATKProperty(TimeVaryingHighShelvingCoefficients<double>, gain, get_gain, set_gain);
}

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
