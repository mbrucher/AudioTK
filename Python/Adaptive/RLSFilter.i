
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
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;
  };

  ATKProperty(RLSFilter<float>, memory, get_memory, set_memory);
  ATKProperty(RLSFilter<float>, learning, get_learning, set_learning);
  ATKProperty(RLSFilter<double>, memory, get_memory, set_memory);
  ATKProperty(RLSFilter<double>, learning, get_learning, set_learning);
  ATKProperty(RLSFilter<std::complex<float> >, memory, get_memory, set_memory);
  ATKProperty(RLSFilter<std::complex<float> >, learning, get_learning, set_learning);
  ATKProperty(RLSFilter<std::complex<double> >, memory, get_memory, set_memory);
  ATKProperty(RLSFilter<std::complex<double> >, learning, get_learning, set_learning);
}

%template(FloatRLSFilter) ATK::RLSFilter<float>;
%template(DoubleRLSFilter) ATK::RLSFilter<double>;
%template(ComplexFloatRLSFilter) ATK::RLSFilter<std::complex<float> >;
%template(ComplexDoubleRLSFilter) ATK::RLSFilter<std::complex<double> >;

%define RLSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32> > get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32> >((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
ATKgetProperty(name, coefficients_in, get_coefficients_in);
%enddef

RLSFilterExtend(ATK::RLSFilter<float>, float);
RLSFilterExtend(ATK::RLSFilter<double>, double);
RLSFilterExtend(ATK::RLSFilter<std::complex<float> >, std::complex<float>);
RLSFilterExtend(ATK::RLSFilter<std::complex<double> >, std::complex<double>);
