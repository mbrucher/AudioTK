
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

%template(FloatSimpleOverdriveFilter) ATK::ApplyGainFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::ApplyGainFilter<double>;
