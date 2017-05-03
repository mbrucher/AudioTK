
%{
#include <ATK/Tools/WhiteNoiseGeneratorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class WhiteNoiseGeneratorFilter: public BaseFilter
  {
  public:
    WhiteNoiseGeneratorFilter();
    ~WhiteNoiseGeneratorFilter();
    
    void set_volume(DataType volume);
    DataType get_volume();
    void set_offset(DataType offset);
    DataType get_offset();
  };

  ATKProperty(WhiteNoiseGeneratorFilter<float>, volume, get_volume, set_volume);
  ATKProperty(WhiteNoiseGeneratorFilter<float>, offset, get_offset, set_offset);
  ATKProperty(WhiteNoiseGeneratorFilter<double>, volume, get_volume, set_volume);
  ATKProperty(WhiteNoiseGeneratorFilter<double>, offset, get_offset, set_offset);
}

%template(FloatWhiteNoiseGeneratorFilter) ATK::WhiteNoiseGeneratorFilter<float>;
%template(DoubleWhiteNoiseGeneratorFilter) ATK::WhiteNoiseGeneratorFilter<double>;
