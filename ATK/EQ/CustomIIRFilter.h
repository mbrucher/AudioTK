/**
 * \file CustomIIRFilter.h
 */

#ifndef ATK_EQ_CUSTOMIIRFILTER_H
#define ATK_EQ_CUSTOMIIRFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class CustomIIRCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    int in_order;
    int out_order;

    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;

  public:
    CustomIIRCoefficients(int nb_channels = 1);

    /**
     * Set custom coefficients for the IIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
     */
    void set_coefficients_in(const std::vector<DataType>& coefficients_in);
    /**
     * Set custom coefficients for the IIR filter (usually called a in the literature). As for coefficients_in, the order is reverse, and the coefficient for lag 0 must be omitted.
     * The coefficients will be used directly in the computation (y[n] = sum(x[n-m+k]*b[k]) + sum(y[n-l+k]*a[k], k!=0) with m, l the order of b, a respectively)
     */
    void set_coefficients_out(const std::vector<DataType>& coefficients_out);
  };
}

#endif
