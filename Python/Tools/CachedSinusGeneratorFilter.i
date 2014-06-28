
%{
#include <ATK/Tools/CachedSinusGeneratorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class CachedSinusGeneratorFilter: public BaseFilter
  {
  public:
    CachedSinusGeneratorFilter(int periods, int seconds);
    ~CachedSinusGeneratorFilter();
    
    void set_volume(double volume);
    double get_volume();
    void set_offset(double offset);
    double get_offset();
  };
}

%template(FloatCachedSinusGeneratorFilter) ATK::CachedSinusGeneratorFilter<float>;
%template(DoubleCachedSinusGeneratorFilter) ATK::CachedSinusGeneratorFilter<double>;
