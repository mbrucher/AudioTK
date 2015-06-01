
%{
#include <ATK/EQ/LinkwitzRileyFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class LowPassLinkwitzRileyFilterCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  };
  
  template<class DataType>
  class HighPassLinkwitzRileyFilterCoefficients: public BaseSecondOrderCoefficients<DataType>
  {
  };
}

%template(FloatLowPassLinkwitzRileyFilterCoefficients) ATK::LowPassLinkwitzRileyFilterCoefficients<float>;
%template(DoubleLowPassLinkwitzRileyFilterCoefficients) ATK::LowPassLinkwitzRileyFilterCoefficients<double>;
%template(FloatHighPassLinkwitzRileyFilterCoefficients) ATK::HighPassLinkwitzRileyFilterCoefficients<float>;
%template(DoubleHighPassLinkwitzRileyFilterCoefficients) ATK::HighPassLinkwitzRileyFilterCoefficients<double>;


%template(FloatLowPassLinkwitzRileyFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowPassLinkwitzRileyFilterCoefficients<float> >;
%template(DoubleLowPassLinkwitzRileyFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::LowPassLinkwitzRileyFilterCoefficients<double> >;
%template(FloatHighPassLinkwitzRileyFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighPassLinkwitzRileyFilterCoefficients<float> >;
%template(DoubleHighPassLinkwitzRileyFilterCoefficientsIIRFilter) ATK::IIRFilter<ATK::HighPassLinkwitzRileyFilterCoefficients<double> >;
