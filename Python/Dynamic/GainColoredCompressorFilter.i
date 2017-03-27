
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
}

%template() ATK::GainColoredCompressorFilter<float>;
%template() ATK::GainColoredCompressorFilter<double>;
%template(FloatGainColoredCompressorFilter) ATK::GainFilter<ATK::GainColoredCompressorFilter<float>>;
%template(DoubleGainColoredCompressorFilter) ATK::GainFilter<ATK::GainColoredCompressorFilter<double>>;
