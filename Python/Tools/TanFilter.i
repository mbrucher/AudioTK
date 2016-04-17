
%{
#include <ATK/Tools/TanFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class TanFilter: public BaseFilter
  {
  public:
    TanFilter(int nb_channels = 1);
    ~TanFilter();
  };
}

%template(FloatTanFilter) ATK::TanFilter<float>;
%template(DoubleTanFilter) ATK::TanFilter<double>;
