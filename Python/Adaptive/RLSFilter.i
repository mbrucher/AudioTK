
%{
#include <ATK/Adaptive/RLSFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class RLSFilter: public BaseFilter
  {
  public:
    RLSFilter(std::size_t size);
    ~RLSFilter();
    
    /// Sets the memory of the RLS algorithm
    void set_memory(DataType memory);
    /// Retrieves the memory
    DataType get_memory() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;
  };
}

%template(FloatRLSFilter) ATK::RLSFilter<float>;
%template(DoubleRLSFilter) ATK::RLSFilter<double>;
%template(ComplexFloatRLSFilter) ATK::RLSFilter<std::complex<float>>;
%template(ComplexDoubleRLSFilter) ATK::RLSFilter<std::complex<double>>;

%define RLSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32>>((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
%enddef

RLSFilterExtend(ATK::RLSFilter<float>, float);
RLSFilterExtend(ATK::RLSFilter<double>, double);
RLSFilterExtend(ATK::RLSFilter<std::complex<float>>, std::complex<float>);
RLSFilterExtend(ATK::RLSFilter<std::complex<double>>, std::complex<double>);
