
%{
#include <ATK/EQ/RobertBristowJohnsonFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class RobertBristowJohnsonLowPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonHighPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };

  template<class DataType>
  class RobertBristowJohnsonBandPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonBandPass2Coefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonBandStopCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };

  template<class DataType>
  class RobertBristowJohnsonAllPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonBandPassPeakCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType Q);
    DataType get_gain() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonLowShelvingCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType Q);
    DataType get_gain() const;
  };
  
  template<class DataType>
  class RobertBristowJohnsonHighShelvingCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  public:
    void set_Q(DataType Q);
    DataType get_Q() const;
    void set_gain(DataType Q);
    DataType get_gain() const;
  };

  ATKProperty(IIRFilter<RobertBristowJohnsonLowPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandStopCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandStopCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandStopCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandStopCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float> >, gain, get_gain, set_gain);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double> >, Q, get_Q, set_Q);
  ATKProperty(IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double> >, gain, get_gain, set_gain);
}

%template(FloatRobertBristowJohnsonLowPassFilterCoefficients) ATK::RobertBristowJohnsonLowPassCoefficients<float>;
%template(DoubleRobertBristowJohnsonLowPassFilterCoefficients) ATK::RobertBristowJohnsonLowPassCoefficients<double>;
%template(FloatRobertBristowJohnsonHighPassFilterCoefficients) ATK::RobertBristowJohnsonHighPassCoefficients<float>;
%template(DoubleRobertBristowJohnsonHighPassFilterCoefficients) ATK::RobertBristowJohnsonHighPassCoefficients<double>;
%template(FloatRobertBristowJohnsonBandPassFilterCoefficients) ATK::RobertBristowJohnsonBandPassCoefficients<float>;
%template(DoubleRobertBristowJohnsonBandPassFilterCoefficients) ATK::RobertBristowJohnsonBandPassCoefficients<double>;
%template(FloatRobertBristowJohnsonBandPass2FilterCoefficients) ATK::RobertBristowJohnsonBandPass2Coefficients<float>;
%template(DoubleRobertBristowJohnsonBandPass2FilterCoefficients) ATK::RobertBristowJohnsonBandPass2Coefficients<double>;
%template(FloatRobertBristowJohnsonBandStopFilterCoefficients) ATK::RobertBristowJohnsonBandStopCoefficients<float>;
%template(DoubleRobertBristowJohnsonBandStopFilterCoefficients) ATK::RobertBristowJohnsonBandStopCoefficients<double>;
%template(FloatRobertBristowJohnsonAllPassFilterCoefficients) ATK::RobertBristowJohnsonAllPassCoefficients<float>;
%template(DoubleRobertBristowJohnsonAllPassFilterCoefficients) ATK::RobertBristowJohnsonAllPassCoefficients<double>;
%template(FloatRobertBristowJohnsonBandPassPeakFilterCoefficients) ATK::RobertBristowJohnsonBandPassPeakCoefficients<float>;
%template(DoubleRobertBristowJohnsonBandPassPeakFilterCoefficients) ATK::RobertBristowJohnsonBandPassPeakCoefficients<double>;
%template(FloatRobertBristowJohnsonLowShelvingFilterCoefficients) ATK::RobertBristowJohnsonLowShelvingCoefficients<float>;
%template(DoubleRobertBristowJohnsonLowShelvingFilterCoefficients) ATK::RobertBristowJohnsonLowShelvingCoefficients<double>;
%template(FloatRobertBristowJohnsonHighShelvingFilterCoefficients) ATK::RobertBristowJohnsonHighShelvingCoefficients<float>;
%template(DoubleRobertBristowJohnsonHighShelvingFilterCoefficients) ATK::RobertBristowJohnsonHighShelvingCoefficients<double>;

%template(FloatRobertBristowJohnsonLowPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<float> >;
%template(DoubleRobertBristowJohnsonLowPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> >;
%template(FloatRobertBristowJohnsonHighPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<float> >;
%template(DoubleRobertBristowJohnsonHighPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> >;
%template(FloatRobertBristowJohnsonBandPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<float> >;
%template(DoubleRobertBristowJohnsonBandPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> >;
%template(FloatRobertBristowJohnsonBandPass2Filter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<float> >;
%template(DoubleRobertBristowJohnsonBandPass2Filter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> >;
%template(FloatRobertBristowJohnsonBandStopFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<float> >;
%template(DoubleRobertBristowJohnsonBandStopFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> >;
%template(FloatRobertBristowJohnsonAllPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<float> >;
%template(DoubleRobertBristowJohnsonAllPassFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> >;
%template(FloatRobertBristowJohnsonBandPassPeakFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<float> >;
%template(DoubleRobertBristowJohnsonBandPassPeakFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> >;
%template(FloatRobertBristowJohnsonLowShelvingFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<float> >;
%template(DoubleRobertBristowJohnsonLowShelvingFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> >;
%template(FloatRobertBristowJohnsonHighShelvingFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<float> >;
%template(DoubleRobertBristowJohnsonHighShelvingFilter) ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonHighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPass2Coefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandStopCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonAllPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonBandPassPeakCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonLowShelvingCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RobertBristowJohnsonHighShelvingCoefficients<double> >, double);
