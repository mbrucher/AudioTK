
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
}

%template() ATK::GainColoredExpanderFilter<float>;
%template() ATK::GainColoredExpanderFilter<double>;
%template(FloatGainColoredExpanderFilter) ATK::GainFilter<ATK::GainColoredExpanderFilter<float>>;
%template(DoubleGainColoredExpanderFilter) ATK::GainFilter<ATK::GainColoredExpanderFilter<double>>;
