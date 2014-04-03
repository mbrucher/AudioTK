
%{
#include <ATK/EQ/ButterworthFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ButterworthLowPassCoefficients: public BaseFilter
  {
  public:
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
}

%template(FloatButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<float>;
%template(DoubleButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<double>;
