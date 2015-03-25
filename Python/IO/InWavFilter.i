
%{
#include <ATK/IO/InWavFilter.h>
%}

%include <std_string.i>

namespace ATK
{
  template<class DataType>
  class InWavFilter: public BaseFilter
  {
  public:
    InWavFilter(std::string filename);
    ~InWavFilter();
  };
}

%template(FloatInWavFilter) ATK::InWavFilter<float>;
%template(DoubleInWavFilter) ATK::InWavFilter<double>;
