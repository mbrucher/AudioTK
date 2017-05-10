
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

  ATKProperty(GainLimiterFilter<float>, threshold, get_threshold, set_threshold);
  ATKProperty(GainLimiterFilter<float>, softness, get_softness, set_softness);
  ATKProperty(GainLimiterFilter<double>, threshold, get_threshold, set_threshold);
  ATKProperty(GainLimiterFilter<double>, softness, get_softness, set_softness);
}

%template() ATK::GainLimiterFilter<float>;
%template() ATK::GainLimiterFilter<double>;
%template(FloatGainLimiterFilter) ATK::GainFilter<ATK::GainLimiterFilter<float> >;
%template(DoubleGainLimiterFilter) ATK::GainFilter<ATK::GainLimiterFilter<double> >;
