
%{
#include <ATK/Dynamic/GainExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainExpanderFilter: public BaseFilter
  {
  public:
    GainExpanderFilter(int nb_channels = 1);
    ~GainExpanderFilter();
  };

  ATKProperty(GainFilter<GainExpanderFilter<float>>, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainExpanderFilter<float>>, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainExpanderFilter<double>>, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainExpanderFilter<double>>, softness, get_softness, set_softness);
}

%template() ATK::GainExpanderFilter<float>;
%template() ATK::GainExpanderFilter<double>;
%template(FloatGainExpanderFilter) ATK::GainFilter<ATK::GainExpanderFilter<float>>;
%template(DoubleGainExpanderFilter) ATK::GainFilter<ATK::GainExpanderFilter<double>>;
