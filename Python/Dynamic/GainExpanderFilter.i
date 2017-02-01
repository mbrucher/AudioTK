
%{
#include <ATK/Dynamic/GainExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainExpanderFilter: public BaseFilter
  {
  public:
    GainExpanderFilter(int nb_channels = 1);
    ~GainExpanderFilter();
  };
}

%template() ATK::GainExpanderFilter<float>;
%template() ATK::GainExpanderFilter<double>;
%template(FloatGainExpanderFilter) ATK::GainFilter<ATK::GainExpanderFilter<float>>;
%template(DoubleGainExpanderFilter) ATK::GainFilter<ATK::GainExpanderFilter<double>>;
