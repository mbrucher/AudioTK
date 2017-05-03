
%{
#include <ATK/EQ/LinkwitzRileyFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class LinkwitzRileyLowPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class LinkwitzRileyHighPassCoefficients: public SecondOrderBaseCoefficients<DataType>
  {
  };
  
  ATKProperty(IIRFilter<LinkwitzRileyLowPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<LinkwitzRileyLowPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<LinkwitzRileyHighPassCoefficients<float> >, cut_frequency, get_cut_frequency, set_cut_frequency);
  ATKProperty(IIRFilter<LinkwitzRileyHighPassCoefficients<double> >, cut_frequency, get_cut_frequency, set_cut_frequency);
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
