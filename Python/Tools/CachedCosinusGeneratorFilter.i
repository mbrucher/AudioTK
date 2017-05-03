
%{
#include <ATK/Tools/CachedCosinusGeneratorFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class CachedCosinusGeneratorFilter: public BaseFilter
  {
  public:
    CachedCosinusGeneratorFilter(int periods, int seconds);
    ~CachedCosinusGeneratorFilter();
    
    void set_frequency(int periods, int seconds = 1);
    std::pair<int, int> get_frequency() const;
    void set_volume(double volume);
    double get_volume();
    void set_offset(double offset);
    double get_offset();
  };

  ATKProperty(CachedCosinusGeneratorFilter<float>, volume, get_volume, set_volume);
  ATKProperty(CachedCosinusGeneratorFilter<float>, offset, get_offset, set_offset);
  ATKProperty(CachedCosinusGeneratorFilter<double>, volume, get_volume, set_volume);
  ATKProperty(CachedCosinusGeneratorFilter<double>, offset, get_offset, set_offset);
}

%template(FloatCachedCosinusGeneratorFilter) ATK::CachedCosinusGeneratorFilter<float>;
%template(DoubleCachedCosinusGeneratorFilter) ATK::CachedCosinusGeneratorFilter<double>;
