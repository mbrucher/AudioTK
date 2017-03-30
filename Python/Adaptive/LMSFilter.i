
%{
#include <ATK/Adaptive/LMSFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class LMSFilter: public BaseFilter
  {
  public:
    LMSFilter(std::size_t size);
    ~LMSFilter();
    
    /// Sets the memory of the LMS algorithm
    void set_memory(DataType memory);
    /// Retrieves the memory
    DataType get_memory() const;

    /// Sets mu
    void set_mu(DataType mu);
    /// Retrieves mu
    DataType get_mu() const;

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

%template(FloatLMSFilter) ATK::LMSFilter<float>;
%template(DoubleLMSFilter) ATK::LMSFilter<double>;

%define LMSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32>> get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32>>((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
%enddef

LMSFilterExtend(ATK::LMSFilter<float>, float);
LMSFilterExtend(ATK::LMSFilter<double>, double);
