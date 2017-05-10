
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

  ATKProperty(GainSwellFilter<float>, threshold, get_threshold, set_threshold);
  ATKProperty(GainSwellFilter<float>, softness, get_softness, set_softness);
  ATKProperty(GainSwellFilter<double>, threshold, get_threshold, set_threshold);
  ATKProperty(GainSwellFilter<double>, softness, get_softness, set_softness);
}

%template() ATK::GainSwellFilter<float>;
%template() ATK::GainSwellFilter<double>;
%template(FloatGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<float> >;
%template(DoubleGainSwellFilter) ATK::GainFilter<ATK::GainSwellFilter<double> >;
