
%{
#include <ATK/Dynamic/GainColoredExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainColoredExpanderFilter: public BaseFilter
  {
  public:
    GainColoredExpanderFilter(int nb_channels = 1);
    ~GainColoredExpanderFilter();

    void set_color(DataType color);
    DataType get_color() const;
    void set_quality(DataType quality);
    DataType get_quality() const;
  };
  
  ATKProperty(GainColoredExpanderFilter<float>, threshold, get_threshold, set_threshold);
  ATKProperty(GainColoredExpanderFilter<float>, softness, get_softness, set_softness);
  ATKProperty(GainColoredExpanderFilter<float>, color, get_color, set_color);
  ATKProperty(GainColoredExpanderFilter<float>, quality, get_quality, set_quality);
  ATKProperty(GainColoredExpanderFilter<double>, threshold, get_threshold, set_threshold);
  ATKProperty(GainColoredExpanderFilter<double>, softness, get_softness, set_softness);
  ATKProperty(GainColoredExpanderFilter<double>, color, get_color, set_color);
  ATKProperty(GainColoredExpanderFilter<double>, quality, get_quality, set_quality);
}

%template() ATK::GainColoredExpanderFilter<float>;
%template() ATK::GainColoredExpanderFilter<double>;
%template(FloatGainColoredExpanderFilter) ATK::GainFilter<ATK::GainColoredExpanderFilter<float> >;
%template(DoubleGainColoredExpanderFilter) ATK::GainFilter<ATK::GainColoredExpanderFilter<double> >;
