
%{
#include <ATK/Dynamic/PowerFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class PowerFilter: public BaseFilter
  {
  public:
    PowerFilter(int nb_channels = 1);
    ~PowerFilter();

    void set_memory(DataType memory_factor);
    DataType get_memory() const;
  };

  ATKProperty(GainFilter<PowerFilter<float>>, memory, get_memory, set_memory);
  ATKProperty(GainFilter<PowerFilter<double>>, memory, get_memory, set_memory);
}

%template(FloatPowerFilter) ATK::PowerFilter<float>;
%template(DoublePowerFilter) ATK::PowerFilter<double>;
