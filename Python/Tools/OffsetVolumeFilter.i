
%{
#include <ATK/Tools/OffsetVolumeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class OffsetVolumeFilter: public BaseFilter
  {
  public:
    OffsetVolumeFilter(int nb_channels = 1);
    ~OffsetVolumeFilter();

    void set_volume(double volume);
    double get_volume() const;

    void set_offset(double offset);
    double get_offset() const;
  };
}

%template(FloatOffsetVolumeFilter) ATK::OffsetVolumeFilter<float>;
%template(DoubleOffsetVolumeFilter) ATK::OffsetVolumeFilter<double>;
