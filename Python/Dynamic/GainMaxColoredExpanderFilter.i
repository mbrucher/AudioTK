
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
}

%template() ATK::GainMaxColoredExpanderFilter<float>;
%template() ATK::GainMaxColoredExpanderFilter<double>;
%template(FloatGainMaxColoredExpanderFilter) ATK::GainFilter<ATK::GainMaxColoredExpanderFilter<float>>;
%template(DoubleGainMaxColoredExpanderFilter) ATK::GainFilter<ATK::GainMaxColoredExpanderFilter<double>>;
