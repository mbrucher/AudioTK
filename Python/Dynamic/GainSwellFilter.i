
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

  ATKProperty(GainFilter<GainSwellFilter<float> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainSwellFilter<float> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainSwellFilter<float> >, ratio, get_ratio, set_ratio);
  ATKProperty(GainFilter<GainSwellFilter<double> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainSwellFilter<double> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainSwellFilter<double> >, ratio, get_ratio, set_ratio);
}

%template() ATK::GainSwellFilter<float>;
%template() ATK::GainSwellFilter<double>;
%template(FloatGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<float> >;
%template(DoubleGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<double> >;
