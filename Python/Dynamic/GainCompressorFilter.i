
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

  ATKProperty(GainCompressorFilter<float>, threshold, get_threshold, set_threshold);
  ATKProperty(GainCompressorFilter<float>, softness, get_softness, set_softness);
  ATKProperty(GainCompressorFilter<double>, threshold, get_threshold, set_threshold);
  ATKProperty(GainCompressorFilter<double>, softness, get_softness, set_softness);
}

%template() ATK::GainCompressorFilter<float>;
%template() ATK::GainCompressorFilter<double>;
%template(FloatGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<float> >;
%template(DoubleGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<double> >;
