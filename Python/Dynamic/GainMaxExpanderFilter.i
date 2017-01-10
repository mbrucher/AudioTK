
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

    void set_max_reduction(DataType max_reduction);
    void set_max_reduction_db(DataType max_reduction);
    DataType get_max_reduction() const;
  };
}

%template(FloatGainMaxExpanderFilter) ATK::GainFilter<ATK::GainMaxExpanderFilter<float>>;
%template(DoubleGainMaxExpanderFilter) ATK::GainFilter<ATK::GainMaxExpanderFilter<double>>;
