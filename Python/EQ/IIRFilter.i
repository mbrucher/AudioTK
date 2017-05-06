
%{
#include <ATK/EQ/IIRFilter.h>
%}

namespace ATK
{
  template<class Coefficients>
  class IIRFilter: public Coefficients
  {
  public:
    IIRFilter(int nb_channels = 1);
    ~IIRFilter();
    void process(long size);
  };
}

%define IIRFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return (*self).get_coefficients_in();
  }
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_out()
  {
    return (*self).get_coefficients_out();
  }
}
ATKgetProperty(name, coefficients_in, get_coefficients_in);
ATKgetProperty(name, coefficients_out, get_coefficients_out);
%enddef
