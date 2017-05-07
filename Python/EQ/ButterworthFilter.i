
%{
#include <ATK/EQ/ButterworthFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ButterworthLowPassCoefficients: public BaseFilter
  {
  public:
    ButterworthLowPassCoefficients();
    ~ButterworthLowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class ButterworthHighPassCoefficients: public BaseFilter
  {
  public:
    ButterworthHighPassCoefficients();
    ~ButterworthHighPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };

  template<class DataType>
  class ButterworthBandPassCoefficients: public BaseFilter
  {
  public:
    ButterworthBandPassCoefficients();
    ~ButterworthBandPassCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class ButterworthBandStopCoefficients: public BaseFilter
  {
  public:
    ButterworthBandStopCoefficients();
    ~ButterworthBandStopCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };

  ATKProperty(ButterworthLowPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(ButterworthLowPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(ButterworthHighPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(ButterworthHighPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
}

%template(FloatButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<float>;
%template(DoubleButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<double>;
%template(FloatButterworthHighPassCoefficients) ATK::ButterworthHighPassCoefficients<float>;
%template(DoubleButterworthHighPassCoefficients) ATK::ButterworthHighPassCoefficients<double>;
%template(FloatButterworthBandPassCoefficients) ATK::ButterworthBandPassCoefficients<float>;
%template(DoubleButterworthBandPassCoefficients) ATK::ButterworthBandPassCoefficients<double>;
%template(FloatButterworthBandStopCoefficients) ATK::ButterworthBandStopCoefficients<float>;
%template(DoubleButterworthBandPStopCoefficients) ATK::ButterworthBandStopCoefficients<double>;

%template(FloatButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >;
%template(DoubleButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >;
%template(FloatButterworthHighPassFilter) ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<float> >;
%template(DoubleButterworthHighPassFilter) ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<double> >;
%template(FloatButterworthBandPassFilter) ATK::IIRFilter<ATK::ButterworthBandPassCoefficients<float> >;
%template(DoubleButterworthBandPassFilter) ATK::IIRFilter<ATK::ButterworthBandPassCoefficients<double> >;
%template(FloatButterworthBandStopFilter) ATK::IIRFilter<ATK::ButterworthBandStopCoefficients<float> >;
%template(DoubleButterworthBandStopFilter) ATK::IIRFilter<ATK::ButterworthBandStopCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthBandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthBandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthBandStopCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthBandStopCoefficients<double> >, double);
