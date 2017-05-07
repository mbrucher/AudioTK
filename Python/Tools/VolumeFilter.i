
%{
#include <ATK/Tools/VolumeFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class VolumeFilter: public BaseFilter
  {
  public:
    VolumeFilter(int nb_channels = 1);
    ~VolumeFilter();
    void set_volume(DataType volume);
    void set_volume_db(double volume_db);
    DataType get_volume() const;
  };

  ATKProperty(VolumeFilter<std::int16_t>, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<std::int32_t>, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<std::int64_t>, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<float>, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<double>, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<std::complex<float> >, volume, get_volume, set_volume);
  ATKProperty(VolumeFilter<std::complex<double> >, volume, get_volume, set_volume);
}

%template(Int16VolumeFilter) ATK::VolumeFilter<std::int16_t>;
%template(Int32VolumeFilter) ATK::VolumeFilter<std::int32_t>;
%template(Int64VolumeFilter) ATK::VolumeFilter<std::int64_t>;
%template(FloatVolumeFilter) ATK::VolumeFilter<float>;
%template(DoubleVolumeFilter) ATK::VolumeFilter<double>;
%template(ComplexFloatVolumeFilter) ATK::VolumeFilter<std::complex<float> >;
%template(ComplexDoubleVolumeFilter) ATK::VolumeFilter<std::complex<double> >;
