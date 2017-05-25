
%{
#include <ATK/Dynamic/GainFilter.h>
%}

namespace ATK
{
  template<class ParentFilter>
  class GainFilter: public ParentFilter, public BaseFilter
  {
  public:
    GainFilter(int nb_channels = 1);
    ~GainFilter();

    void set_threshold(double threshold);
    void set_threshold_db(double threshold);
    double get_threshold() const;
    void set_ratio(double ratio);
    double get_ratio() const;
    void set_softness(double softness);
    double get_softness() const;
  };
}
