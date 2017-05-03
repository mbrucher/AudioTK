
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

  ATKProperty(GainFilter<RelativePowerFilter<float>>, memory, get_memory, set_memory);
  ATKProperty(GainFilter<RelativePowerFilter<double>>, memory, get_memory, set_memory);
}

%template(FloatRelativePowerFilter) ATK::RelativePowerFilter<float>;
%template(DoubleRelativePowerFilter) ATK::RelativePowerFilter<double>;
