
%{
#include <ATK/Dynamic/GainFractionalCompressorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainFractionalCompressorFilter: public BaseFilter
  {
  public:
    GainFractionalCompressorFilter(int nb_channels = 1);
    ~GainFractionalCompressorFilter();

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_ratio(DataType ratio);
    DataType get_ratio() const;
    void set_color(DataType color);
    DataType get_color() const;
  };
}

%template(FloatGainFractionalCompressorFilter) ATK::GainFractionalCompressorFilter<float>;
%template(DoubleGainFractionalCompressorFilter) ATK::GainFractionalCompressorFilter<double>;
