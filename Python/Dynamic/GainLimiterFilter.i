
%{
#include <ATK/Dynamic/GainLimiterFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainLimiterFilter: public BaseFilter
  {
  public:
    GainLimiterFilter(int nb_channels = 1);
    ~GainLimiterFilter();
  };

  ATKProperty(GainFilter<GainLimiterFilter<float> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainLimiterFilter<float> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainLimiterFilter<double> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainLimiterFilter<double> >, softness, get_softness, set_softness);
}

%template() ATK::GainLimiterFilter<float>;
%template() ATK::GainLimiterFilter<double>;
%template(FloatGainLimiterFilter) ATK::GainFilter<ATK::GainLimiterFilter<float> >;
%template(DoubleGainLimiterFilter) ATK::GainFilter<ATK::GainLimiterFilter<double> >;
