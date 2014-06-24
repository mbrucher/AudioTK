
%{
#include <ATK/Dynamic/PowerFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class PowerFilter: public BaseFilter
  {
  public:
    PowerFilter(int nb_channels);
    ~PowerFilter();

    void set_memory(DataType memory_factor);
    DataType get_memory() const;
  };
}

%template(FloatPowerFilter) ATK::PowerFilter<float>;
%template(DoublePowerFilter) ATK::PowerFilter<double>;
