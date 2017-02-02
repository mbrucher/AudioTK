
%{
#include <ATK/EQ/IIRFilter.h>
#include <boost/align/aligned_allocator.hpp>
%}

%include <std_vector.i>

%template(FloatVector) std::vector<float, boost::alignment::aligned_allocator<float, 32>>;
%template(DoubleVector) std::vector<double, boost::alignment::aligned_allocator<double, 32>>;

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
%enddef

%define FIRFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return (*self).get_coefficients_in();
  }
}
%enddef
