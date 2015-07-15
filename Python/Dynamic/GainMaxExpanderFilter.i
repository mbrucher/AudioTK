
%{
#include <ATK/Dynamic/GainMaxExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainMaxExpanderFilter: public BaseFilter
  {
  public:
    GainMaxExpanderFilter(int nb_channels = 1);
    ~GainMaxExpanderFilter();

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
  };
}

%template(FloatGainMaxExpanderFilter) ATK::GainMaxExpanderFilter<float>;
%template(DoubleGainMaxExpanderFilter) ATK::GainMaxExpanderFilter<double>;
