
%{
#include <ATK/EQ/BesselFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class BesselLowPassCoefficients: public BaseFilter
  {
  public:
    BesselLowPassCoefficients();
    ~BesselLowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class BesselHighPassCoefficients: public BaseFilter
  {
  public:
    BesselHighPassCoefficients();
    ~BesselHighPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };

  template<class DataType>
  class BesselBandPassCoefficients: public BaseFilter
  {
  public:
    BesselBandPassCoefficients();
    ~BesselBandPassCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };
  
  template<class DataType>
  class BesselBandStopCoefficients: public BaseFilter
  {
  public:
    BesselBandStopCoefficients();
    ~BesselBandStopCoefficients();
    
    void set_cut_frequencies(DataType f0, DataType f1);
    std::pair<DataType, DataType> get_cut_frequencies() const;
    
    void set_order(int order);
  };

  ATKProperty(IIRFilter<BesselLowPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<BesselLowPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselHighPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<BesselHighPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselHighPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<BesselHighPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselBandPassCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselBandPassCoefficients<double> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselBandStopCoefficients<float> >, ripple, get_ripple, set_ripple);
  ATKProperty(IIRFilter<BesselBandStopCoefficients<double> >, ripple, get_ripple, set_ripple);
}

%template(FloatBesselLowPassCoefficients) ATK::BesselLowPassCoefficients<float>;
%template(DoubleBesselLowPassCoefficients) ATK::BesselLowPassCoefficients<double>;
%template(FloatBesselHighPassCoefficients) ATK::BesselHighPassCoefficients<float>;
%template(DoubleBesselHighPassCoefficients) ATK::BesselHighPassCoefficients<double>;
%template(FloatBesselBandPassCoefficients) ATK::BesselBandPassCoefficients<float>;
%template(DoubleBesselBandPassCoefficients) ATK::BesselBandPassCoefficients<double>;
%template(FloatBesselBandStopCoefficients) ATK::BesselBandStopCoefficients<float>;
%template(DoubleBesselBandPStopCoefficients) ATK::BesselBandStopCoefficients<double>;

%template(FloatBesselLowPassFilter) ATK::IIRFilter<ATK::BesselLowPassCoefficients<float> >;
%template(DoubleBesselLowPassFilter) ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> >;
%template(FloatBesselHighPassFilter) ATK::IIRFilter<ATK::BesselHighPassCoefficients<float> >;
%template(DoubleBesselHighPassFilter) ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> >;
%template(FloatBesselBandPassFilter) ATK::IIRFilter<ATK::BesselBandPassCoefficients<float> >;
%template(DoubleBesselBandPassFilter) ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> >;
%template(FloatBesselBandStopFilter) ATK::IIRFilter<ATK::BesselBandStopCoefficients<float> >;
%template(DoubleBesselBandStopFilter) ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::BesselLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselHighPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselBandPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselBandPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselBandStopCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::BesselBandStopCoefficients<double> >, double);
