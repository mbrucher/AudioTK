
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

%template(FloatGainColoredExpanderFilter) ATK::GainColoredExpanderFilter<float>;
%template(DoubleGainColoredExpanderFilter) ATK::GainColoredExpanderFilter<double>;
