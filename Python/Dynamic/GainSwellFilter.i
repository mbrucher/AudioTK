
%{
#include <ATK/Dynamic/GainSwellFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainSwellFilter: public BaseFilter
  {
  public:
    GainSwellFilter(int nb_channels = 1);
    ~GainSwellFilter();

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_ratio(DataType ratio);
    DataType get_ratio() const;
    void set_softness(DataType softness);
    DataType get_softness() const;
  };
}

%template(FloatGainSwellFilter) ATK::GainSwellFilter<float>;
%template(DoubleGainSwellFilter) ATK::GainSwellFilter<double>;
