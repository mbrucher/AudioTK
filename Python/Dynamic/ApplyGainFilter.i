
%{
#include <ATK/Dynamic/ApplyGainFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ApplyGainFilter: public BaseFilter
  {
  public:
    ApplyGainFilter(int nb_channels);
    ~ApplyGainFilter();
  };
}

%template(FloatApplyGainFilter) ATK::ApplyGainFilter<float>;
%template(DoubleApplyGainFilter) ATK::ApplyGainFilter<double>;
