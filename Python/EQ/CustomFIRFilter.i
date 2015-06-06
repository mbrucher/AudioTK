
%{
#include <ATK/EQ/CustomFIRFilter.h>
%}

%include <std_vector.i>

namespace ATK
{
  template<class DataType>
  class CustomFIRCoefficients: public BaseFilter
  {
  public:
    CustomFIRCoefficients(int channels = 1);
    ~CustomFIRCoefficients();
    
    /**
     * Set custom coefficients for the IIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
     */
    void set_coefficients_in(std::vector<DataType> coefficients_in);
  };
}

%template(FloatCustomFIRCoefficients) ATK::CustomFIRCoefficients<float>;
%template(DoubleCustomFIRCoefficients) ATK::CustomFIRCoefficients<double>;

%template(FloatCustomFIRFilter) ATK::IIRFilter<ATK::CustomFIRCoefficients<float> >;
%template(DoubleCustomFIRFilter) ATK::IIRFilter<ATK::CustomFIRCoefficients<double> >;

FIRFilterExtend(ATK::IIRFilter<ATK::CustomFIRCoefficients<float> >, float);
FIRFilterExtend(ATK::IIRFilter<ATK::CustomFIRCoefficients<double> >, double);
