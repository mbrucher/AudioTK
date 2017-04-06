
%{
#include <ATK/Adaptive/BlockLMSFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class BlockLMSFilter: public BaseFilter
  {
  public:
    BlockLMSFilter(std::size_t size);
    ~BlockLMSFilter();
    
    /// Sets the memory of the LMS algorithm
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;

    /// Sets mu
    void set_mu(double mu);
    /// Retrieves mu
    double get_mu() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;

  };
}

%template(DoubleBlockLMSFilter) ATK::BlockLMSFilter<double>;

%define BlockLMSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32>>((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
%enddef

BlockLMSFilterExtend(ATK::BlockLMSFilter<double>, double);
