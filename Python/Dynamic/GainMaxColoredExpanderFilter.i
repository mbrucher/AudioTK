
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

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_ratio(DataType ratio);
    DataType get_ratio() const;
    void set_softness(DataType softness);
    DataType get_softness() const;
    void set_max_reduction(DataType max_reduction);
    void set_max_reduction_db(DataType max_reduction);
    DataType get_max_reduction() const;
    void set_color(DataType color);
    DataType get_color() const;
    void set_quality(DataType quality);
    DataType get_quality() const;
  };
}

%template(FloatGainMaxColoredExpanderFilter) ATK::GainMaxColoredExpanderFilter<float>;
%template(DoubleGainMaxColoredExpanderFilter) ATK::GainMaxColoredExpanderFilter<double>;
