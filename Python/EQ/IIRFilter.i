
%{
#include <ATK/EQ/IIRFilter.h>
%}

namespace ATK
{
  template<class Coefficients >
  class IIRFilter: public Coefficients
  {
  public:
    IIRFilter();
    ~IIRFilter();
    void process(long size);
  };
}
