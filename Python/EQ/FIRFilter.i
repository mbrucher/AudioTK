
%{
#include <ATK/EQ/FIRFilter.h>
%}

namespace ATK
{
  template<class Coefficients>
  class FIRFilter: public Coefficients
  {
  public:
    FIRFilter(int nb_channels = 1);
    ~FIRFilter();
    void process(long size);
  };
}

%define FIRFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return (*self).get_coefficients_in();
  }
}
ATKgetProperty(name, coefficients_in, get_coefficients_in);
%enddef
