
%{
#include <ATK/EQ/LinkwitzRileyFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class LinkwitzRileyLowPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };
  
  template<class DataType>
  class LinkwitzRileyHighPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };

  template<class DataType>
  class LinkwitzRiley4LowPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };
  
  template<class DataType>
  class LinkwitzRiley4HighPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency();
  };
  
  ATKProperty(LinkwitzRileyLowPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyLowPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyHighPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyHighPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);

  ATKProperty(LinkwitzRiley4LowPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRiley4LowPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRiley4HighPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRiley4HighPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
}

%template(FloatLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<float>;
%template(DoubleLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<double>;
%template(FloatLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<float>;
%template(DoubleLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<double>;

%template(FloatLinkwitzRiley4LowPassFilterCoefficients) ATK::LinkwitzRiley4LowPassCoefficients<float>;
%template(DoubleLinkwitzRiley4LowPassFilterCoefficients) ATK::LinkwitzRiley4LowPassCoefficients<double>;
%template(FloatLinkwitzRiley4HighPassFilterCoefficients) ATK::LinkwitzRiley4HighPassCoefficients<float>;
%template(DoubleLinkwitzRiley4HighPassFilterCoefficients) ATK::LinkwitzRiley4HighPassCoefficients<double>;

%template(FloatLinkwitzRileyLowPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<float> >;
%template(DoubleLinkwitzRileyLowPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> >;
%template(FloatLinkwitzRileyHighPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<float> >;
%template(DoubleLinkwitzRileyHighPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> >;

%template(FloatLinkwitzRiley4LowPassFilter) ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<float> >;
%template(DoubleLinkwitzRiley4LowPassFilter) ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> >;
%template(FloatLinkwitzRiley4HighPassFilter) ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<float> >;
%template(DoubleLinkwitzRiley4HighPassFilter) ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> >, double);

IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRiley4LowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRiley4HighPassCoefficients<double> >, double);
