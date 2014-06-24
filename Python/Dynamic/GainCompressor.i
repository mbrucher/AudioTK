
%{
#include <ATK/Dynamic/GainCompressorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainCompressorFilter: public BaseFilter
  {
  public:
    GainCompressorFilter(int nb_channels);
    ~GainCompressorFilter();
  };
}

%template(FloatSimpleOverdriveFilter) ATK::GainCompressorFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::GainCompressorFilter<double>;
