
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

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_slope(DataType slope);
    DataType get_slope() const;
    void set_softness(DataType softness);
    DataType get_softness() const;
  };
}

%template(FloatGainExpanderFilter) ATK::GainExpanderFilter<float>;
%template(DoubleGainExpanderFilter) ATK::GainExpanderFilter<double>;
