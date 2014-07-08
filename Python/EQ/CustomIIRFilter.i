
%{
#include <ATK/EQ/CustomIIRFilter.h>
%}

%include <std_vector.i>

namespace ATK
{
  template<class DataType>
  class CustomIIRCoefficients: public BaseFilter
  {
  public:
    CustomIIRCoefficients();
    ~CustomIIRCoefficients();
    
    /**
     * Set custom coefficients for the IIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
     */
    void set_coefficients_in(std::vector<DataType> coefficients_in);
    /**
     * Set custom coefficients for the IIR filter (usually called a in the literature). As for coefficients_in, the order is reverse, and the coefficient for lag 0 must be omitted.
     * The coefficients will be used directly in the computation (y[n] = sum(x[n-m+k]*b[k]) + sum(y[n-l+k]*a[k], k!=0) with m, l the order of b, a respectively)
     */
    void set_coefficients_out(std::vector<DataType> coefficients_out);
  };
}

%template(FloatCustomIIRCoefficients) ATK::CustomIIRCoefficients<float>;
%template(DoubleCustomIIRCoefficients) ATK::CustomIIRCoefficients<double>;

%template(FloatCustomIIRFilter) ATK::IIRFilter<ATK::CustomIIRCoefficients<float> >;
%template(DoubleCustomIIRFilter) ATK::IIRFilter<ATK::CustomIIRCoefficients<double> >;

IIRFilterExtend(ATK::IIRFilter<ATK::CustomIIRCoefficients<float> >, float);
IIRFilterExtend(ATK::IIRFilter<ATK::CustomIIRCoefficients<double> >, double);
