
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
  
  ATKProperty(LinkwitzRileyLowPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyLowPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyHighPassCoefficients<float>, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(LinkwitzRileyHighPassCoefficients<double>, cut_frequency, get_cut_frequency, set_cut_frequency);
}

%template(FloatLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<float>;
%template(DoubleLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<double>;
%template(FloatLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<float>;
%template(DoubleLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<double>;


%template(FloatLinkwitzRileyLowPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<float> >;
%template(DoubleLinkwitzRileyLowPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> >;
%template(FloatLinkwitzRileyHighPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<float> >;
%template(DoubleLinkwitzRileyHighPassFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> >, double);
