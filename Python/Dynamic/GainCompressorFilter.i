
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

  ATKProperty(GainFilter<GainCompressorFilter<float> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainCompressorFilter<float> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainCompressorFilter<double> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainCompressorFilter<double> >, softness, get_softness, set_softness);
}

%template() ATK::GainCompressorFilter<float>;
%template() ATK::GainCompressorFilter<double>;
%template(FloatGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<float> >;
%template(DoubleGainCompressorFilter) ATK::GainFilter<ATK::GainCompressorFilter<double> >;
