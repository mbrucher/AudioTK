
%{
#include <ATK/EQ/ButterworthFilter.h>
%}

%template(FloatVector) std::vector<float>;
%template(DoubleVector) std::vector<double>;

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

IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >, double);
