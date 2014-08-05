
%{
#include <ATK/Tools/DryWetFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class DryWetFilter: public BaseFilter
  {
  public:
    DryWetFilter(int nb_channels = 1);
    ~DryWetFilter();

    void set_dry(double dry);
    double get_dry() const;
  };
}

%template(Int16DryWetFilter) ATK::DryWetFilter<std::int16_t>;
%template(Int32DryWetFilter) ATK::DryWetFilter<std::int32_t>;
%template(Int64DryWetFilter) ATK::DryWetFilter<std::int64_t>;
%template(FloatDryWetFilter) ATK::DryWetFilter<float>;
%template(DoubleDryWetFilter) ATK::DryWetFilter<double>;
