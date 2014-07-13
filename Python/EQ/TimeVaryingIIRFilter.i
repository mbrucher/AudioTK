
%{
#include <ATK/EQ/TimeVaryingIIRFilter.h>
%}

%include <std_vector.i>

namespace ATK
{
  template<class Coefficients>
  class TimeVaryingIIRFilter: public Coefficients
  {
  public:
    TimeVaryingIIRFilter();
    ~TimeVaryingIIRFilter();
    void process(long size);
  };
}

