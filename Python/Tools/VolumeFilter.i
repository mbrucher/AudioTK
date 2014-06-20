
%{
#include <ATK/Tools/VolumeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class VolumeFilter: public BaseFilter
  {
  public:
    VolumeFilter(int nb_channels);
    ~VolumeFilter();
    void set_volume(double volume);
    void set_volume_db(double volume_db);
  };
}

%template(Int16VolumeFilter) ATK::VolumeFilter<std::int16_t>;
%template(Int32VolumeFilter) ATK::VolumeFilter<std::int32_t>;
%template(Int64VolumeFilter) ATK::VolumeFilter<std::int64_t>;
%template(FloatVolumeFilter) ATK::VolumeFilter<float>;
%template(DoubleVolumeFilter) ATK::VolumeFilter<double>;
