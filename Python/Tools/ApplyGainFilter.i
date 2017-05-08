
%{
#include <ATK/Tools/ApplyGainFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ApplyGainFilter: public BaseFilter
  {
  public:
    ApplyGainFilter(int nb_channels = 1);
    ~ApplyGainFilter();
  };
}

%template(FloatApplyGainFilter) ATK::ApplyGainFilter<float>;
%template(DoubleApplyGainFilter) ATK::ApplyGainFilter<double>;
%template(ComplexFloatApplyGainFilter) ATK::ApplyGainFilter<std::complex<float> >;
%template(ComplexDoubleApplyGainFilter) ATK::ApplyGainFilter<std::complex<double> >;
