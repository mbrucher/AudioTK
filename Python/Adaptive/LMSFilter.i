
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
    void set_memory(double memory);
    /// Retrieves the memory
    double get_memory() const;

    /// Sets mu
    void set_mu(double mu);
    /// Retrieves mu
    double get_mu() const;

    enum Mode
    {
      NORMAL,
      NORMALIZED,
      SIGNERROR,
      SIGNDATA,
      SIGNSIGN
    };

    /// Sets the way the filter is updated
    void set_mode(Mode mode);
    /// Retrieves the way the filter is updated
    Mode get_mode() const;

    /// Sets the learning mode
    void set_learning(bool learning);
    /// Am I in learning mode or not?
    bool get_learning() const;
  };

  ATKProperty(LMSFilter<float>, mode, get_mode, set_mode);
  ATKProperty(LMSFilter<float>, learning, get_learning, set_learning);
  ATKProperty(LMSFilter<double>, mode, get_mode, set_mode);
  ATKProperty(LMSFilter<double>, learning, get_learning, set_learning);
}

%template(FloatLMSFilter) ATK::LMSFilter<float>;
%template(DoubleLMSFilter) ATK::LMSFilter<double>;

%define LMSFilterExtend(name, T)
%extend name {
  std::vector<T, boost::alignment::aligned_allocator<T, 32> > get_coefficients_in()
  {
    return std::vector<T, boost::alignment::aligned_allocator<T, 32> >((*self).get_w(), (*self).get_w() + (*self).get_size());;
  }
}
ATKgetProperty(name, coefficients_in, get_coefficients_in);
%enddef

LMSFilterExtend(ATK::LMSFilter<float>, float);
LMSFilterExtend(ATK::LMSFilter<double>, double);
