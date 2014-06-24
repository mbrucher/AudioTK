
%{
#include <ATK/Dynamic/GainCompressorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainCompressorFilter: public BaseFilter
  {
  public:
    GainCompressorFilter(int nb_channels);
    ~GainCompressorFilter();

    void set_threshold(DataType_ threshold);
    DataType_ get_threshold() const;
    void set_slope(DataType_ slope);
    DataType_ get_slope() const;
  };
}

%template(FloatSimpleOverdriveFilter) ATK::GainCompressorFilter<float>;
%template(DoubleSimpleOverdriveFilter) ATK::GainCompressorFilter<double>;
