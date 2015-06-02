
%{
#include <ATK/EQ/LinkwitzRileyFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class LinkwitzRileyLowPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class LinkwitzRileyHighPassCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  };
}

%template(FloatLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<float>;
%template(DoubleLinkwitzRileyLowPassFilterCoefficients) ATK::LinkwitzRileyLowPassCoefficients<double>;
%template(FloatLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<float>;
%template(DoubleLinkwitzRileyHighPassFilterCoefficients) ATK::LinkwitzRileyHighPassCoefficients<double>;


%template(FloatLinkwitzRileyLowPassFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<float> >;
%template(DoubleLinkwitzRileyLowPassFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LinkwitzRileyLowPassCoefficients<double> >;
%template(FloatLinkwitzRileyHighPassFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<float> >;
%template(DoubleLinkwitzRileyHighPassFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LinkwitzRileyHighPassCoefficients<double> >;
