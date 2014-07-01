
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
    
    void set_volume(double volume);
    double get_volume();
    void set_offset(double offset);
    double get_offset();
  };
}

%template(FloatWhiteNoiseGeneratorFilter) ATK::WhiteNoiseGeneratorFilter<float>;
%template(DoubleWhiteNoiseGeneratorFilter) ATK::WhiteNoiseGeneratorFilter<double>;
