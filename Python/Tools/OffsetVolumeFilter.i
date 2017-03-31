
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

    void set_volume(DataType volume);
    DataType get_volume() const;

    void set_offset(DataType offset);
    DataType get_offset() const;
  };
}

%template(FloatOffsetVolumeFilter) ATK::OffsetVolumeFilter<float>;
%template(DoubleOffsetVolumeFilter) ATK::OffsetVolumeFilter<double>;
%template(ComplexFloatOffsetVolumeFilter) ATK::OffsetVolumeFilter<std::complex<float>>;
%template(ComplexDoubleOffsetVolumeFilter) ATK::OffsetVolumeFilter<std::complex<double>>;
