
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

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_ratio(DataType ratio);
    DataType get_ratio() const;
    void set_softness(DataType softness);
    DataType get_softness() const;
    void set_color(DataType color);
    DataType get_color() const;
    void set_quality(DataType quality);
    DataType get_quality() const;
  };
}

%template(FloatGainColoredCompressorFilter) ATK::GainColoredCompressorFilter<float>;
%template(DoubleGainColoredCompressorFilter) ATK::GainColoredCompressorFilter<double>;
