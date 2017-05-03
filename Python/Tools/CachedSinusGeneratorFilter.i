
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
    
    void set_frequency(int periods, int seconds = 1);
    std::pair<int, int> get_frequency() const;
    void set_volume(double volume);
    double get_volume();
    void set_offset(double offset);
    double get_offset();
  };

  ATKProperty(CachedSinusGeneratorFilter<float>, volume, get_volume, set_volume);
  ATKProperty(CachedSinusGeneratorFilter<float>, offset, get_offset, set_offset);
  ATKProperty(CachedSinusGeneratorFilter<double>, volume, get_volume, set_volume);
  ATKProperty(CachedSinusGeneratorFilter<double>, offset, get_offset, set_offset);
}

%template(FloatCachedSinusGeneratorFilter) ATK::CachedSinusGeneratorFilter<float>;
%template(DoubleCachedSinusGeneratorFilter) ATK::CachedSinusGeneratorFilter<double>;
