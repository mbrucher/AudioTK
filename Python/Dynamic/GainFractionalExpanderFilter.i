
%{
#include <ATK/Dynamic/GainFractionalExpanderFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class GainFractionalExpanderFilter: public BaseFilter
  {
  public:
    GainFractionalExpanderFilter(int nb_channels = 1);
    ~GainFractionalExpanderFilter();

    void set_threshold(DataType threshold);
    void set_threshold_db(DataType threshold);
    DataType get_threshold() const;
    void set_ratio(DataType ratio);
    DataType get_ratio() const;
    void set_color(DataType color);
    DataType get_color() const;
  };
}

%template(FloatGainFractionalExpanderFilter) ATK::GainFractionalExpanderFilter<float>;
%template(DoubleGainFractionalExpanderFilter) ATK::GainFractionalExpanderFilter<double>;
