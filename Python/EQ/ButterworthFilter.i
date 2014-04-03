
%{
#include <ATK/EQ/ButterworthFilter.h>
%}

namespace ATK
{
  template<class DataType>
  class ButterworthLowPassCoefficients: public BaseFilter
  {
  public:
    ButterworthLowPassCoefficients();
    ~ButterworthLowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
}

%template(FloatButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<float>;
%template(DoubleButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<double>;

%template(FloatButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >;
%template(DoubleButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >;
