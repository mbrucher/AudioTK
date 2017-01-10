
%{
#include <ATK/Dynamic/GainCompressorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainCompressorFilter: public BaseFilter
  {
  public:
    GainCompressorFilter(int nb_channels = 1);
    ~GainCompressorFilter();
  };
}

%template(FloatGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<float>>;
%template(DoubleGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<double>>;
