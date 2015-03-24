
%{
#include <ATK/Dynamic/RelativePowerFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class RelativePowerFilter: public BaseFilter
  {
  public:
    RelativePowerFilter(int nb_channels = 1);
    ~RelativePowerFilter();

    void set_memory(DataType memory_factor);
    DataType get_memory() const;
  };
}

%template(FloatRelativePowerFilter) ATK::RelativePowerFilter<float>;
%template(DoubleRelativePowerFilter) ATK::RelativePowerFilter<double>;
