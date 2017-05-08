
%{
#include <ATK/Dynamic/GainColoredCompressorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainColoredCompressorFilter: public BaseFilter
  {
  public:
    GainColoredCompressorFilter(int nb_channels = 1);
    ~GainColoredCompressorFilter();

    void set_color(DataType color);
    DataType get_color() const;
    void set_quality(DataType quality);
    DataType get_quality() const;
  };

  ATKProperty(GainFilter<GainColoredCompressorFilter<float> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainColoredCompressorFilter<float> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainColoredCompressorFilter<float> >, color, get_color, set_color);
  ATKProperty(GainFilter<GainColoredCompressorFilter<float> >, quality, get_quality, set_quality);
  ATKProperty(GainFilter<GainColoredCompressorFilter<double> >, threshold, get_threshold, set_threshold);
  ATKProperty(GainFilter<GainColoredCompressorFilter<double> >, softness, get_softness, set_softness);
  ATKProperty(GainFilter<GainColoredCompressorFilter<double> >, color, get_color, set_color);
  ATKProperty(GainFilter<GainColoredCompressorFilter<double> >, quality, get_quality, set_quality);
}

%template() ATK::GainColoredCompressorFilter<float>;
%template() ATK::GainColoredCompressorFilter<double>;
%template(FloatGainColoredCompressorFilter) ATK::GainFilter<ATK::GainColoredCompressorFilter<float> >;
%template(DoubleGainColoredCompressorFilter) ATK::GainFilter<ATK::GainColoredCompressorFilter<double> >;
