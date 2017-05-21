
%{
#include <ATK/EQ/RIAAFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class RIAACoefficients: public BaseFilter
  {
  public:
  };
  
  template<class DataType>
  class InverseRIAACoefficients: public BaseFilter
  {
  public:
  };
}

%template(FloatRIAAFilterCoefficients) ATK::RIAACoefficients<float>;
%template(DoubleRIAAFilterCoefficients) ATK::RIAACoefficients<double>;
%template(FloatInverseRIAAFilterCoefficients) ATK::InverseRIAACoefficients<float>;
%template(DoubleInverseRIAAFilterCoefficients) ATK::InverseRIAACoefficients<double>;

%template(FloatRIAAFilter) ATK::IIRFilter<ATK::RIAACoefficients<float> >;
%template(DoubleRIAAFilter) ATK::IIRFilter<ATK::RIAACoefficients<double> >;
%template(FloatInverseRIAAFilter) ATK::IIRFilter<ATK::InverseRIAACoefficients<float> >;
%template(DoubleInverseRIAAFilter) ATK::IIRFilter<ATK::InverseRIAACoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::RIAACoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::RIAACoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::InverseRIAACoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::InverseRIAACoefficients<double> >, double);
