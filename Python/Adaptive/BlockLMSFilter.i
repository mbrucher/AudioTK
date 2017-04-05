
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

    enum class Mode
    {
      NORMAL,
      NORMALIZED,
      SIGNERROR
    };

    /// Sets the way the filter is updated
    void set_mode(Mode mode);
    /// Retrieves the way the filter is updated
    Mode get_mode() const;
  };
}

%template(FloatBlockLMSFilter) ATK::BlockLMSFilter<float>;
%template(DoubleBlockLMSFilter) ATK::BlockLMSFilter<double>;

%define BlockLMSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32>>((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
%enddef

BlockLMSFilterExtend(ATK::BlockLMSFilter<float>, float);
BlockLMSFilterExtend(ATK::BlockLMSFilter<double>, double);
