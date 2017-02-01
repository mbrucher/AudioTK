
%{
#include <ATK/Dynamic/GainFilter.h>
%}

namespace ATK
{
  template<class ParentFilter>
  class GainFilter: public ParentFilter
  {
  public:
    GainFilter(int nb_channels = 1);
    ~GainFilter();

    void set_threshold(ParentFilter::DataType threshold);
    void set_threshold_db(ParentFilter::DataType threshold);
    ParentFilter::DataType get_threshold() const;
    void set_ratio(ParentFilter::DataType ratio);
    ParentFilter::DataType get_ratio() const;
    void set_softness(ParentFilter::DataType softness);
    ParentFilter::DataType get_softness() const;
  };
}
