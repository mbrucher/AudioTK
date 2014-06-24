
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

    void set_threshold(DataType threshold);
    DataType get_threshold() const;
    void set_slope(DataType slope);
    DataType get_slope() const;
  };
}

%template(FloatGainCompressorFilter) ATK::GainCompressorFilter<float>;
%template(DoubleGainCompressorFilter) ATK::GainCompressorFilter<double>;
