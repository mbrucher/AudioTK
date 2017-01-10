
%{
#include <ATK/Dynamic/GainSwellFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainSwellFilter: public BaseFilter
  {
  public:
    GainSwellFilter(int nb_channels = 1);
    ~GainSwellFilter();
  };
}

%template(FloatGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<float>>;
%template(DoubleGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<double>>;
