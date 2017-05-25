
%{
#include <ATK/Dynamic/GainMaxColoredExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainMaxColoredExpanderFilter: public BaseFilter
  {
  public:
    GainMaxColoredExpanderFilter(int nb_channels = 1);
    ~GainMaxColoredExpanderFilter();

    void set_max_reduction(DataType max_reduction);
    void set_max_reduction_db(DataType max_reduction);
    DataType get_max_reduction() const;
    void set_color(DataType color);
    DataType get_color() const;
    void set_quality(DataType quality);
    DataType get_quality() const;
  };

  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, ratio, get_ratio, set_ratio);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, color, get_color, set_color);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, quality, get_quality, set_quality);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<float> >, max_reduction, get_max_reduction, set_max_reduction);
  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, ratio, get_ratio, set_ratio);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, color, get_color, set_color);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, quality, get_quality, set_quality);
//  ATKProperty(GainFilter<GainMaxColoredExpanderFilter<double> >, max_reduction, get_max_reduction, set_max_reduction);
}

%template() ATK::GainMaxColoredExpanderFilter<float>;
%template() ATK::GainMaxColoredExpanderFilter<double>;
%template(FloatGainMaxColoredExpanderFilter) ATK::GainFilter<ATK::GainMaxColoredExpanderFilter<float> >;
%template(DoubleGainMaxColoredExpanderFilter) ATK::GainFilter<ATK::GainMaxColoredExpanderFilter<double> >;
