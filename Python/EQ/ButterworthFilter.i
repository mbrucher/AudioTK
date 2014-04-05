
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

  template<class DataType>
  class ButterworthHighPassCoefficients: public BaseFilter
  {
  public:
    ButterworthHighPassCoefficients();
    ~ButterworthHighPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
}

%template(FloatButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<float>;
%template(DoubleButterworthLowPassCoefficients) ATK::ButterworthLowPassCoefficients<double>;
%template(FloatButterworthHighPassCoefficients) ATK::ButterworthHighPassCoefficients<float>;
%template(DoubleButterworthHighPassCoefficients) ATK::ButterworthHighPassCoefficients<double>;

%template(FloatButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >;
%template(DoubleButterworthLowPassFilter) ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >;
%template(FloatButterworthHighPassFilter) ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<float> >;
%template(DoubleButterworthHighPassFilter) ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthLowPassCoefficients<double> >, double);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::ButterworthHighPassCoefficients<double> >, double);
