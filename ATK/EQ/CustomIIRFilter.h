/**
 * \file CustomIIRFilter.h
 */

#ifndef ATK_EQ_CUSTOMIIRFILTER_H
#define ATK_EQ_CUSTOMIIRFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Creates a custom IIR filter  when used as the coefficients class with IIRFilter
  template<typename DataType_>
  class CustomIIRCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    /// Order of the MA polynome
    int in_order;
    /// Order of the AR polynome
    int out_order;

    /// MA polynome
    std::vector<DataType> coefficients_in;
    /// AR polynome with order 0 ommitted and supposed to be -1
    std::vector<DataType> coefficients_out;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    CustomIIRCoefficients(int nb_channels = 1);

    /// Set custom coefficients for the IIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
    void set_coefficients_in(std::vector<DataType> coefficients_in);
    /// Set custom coefficients for the IIR filter (usually called a in the literature). As for coefficients_in, the order is reverse, and the coefficient for lag 0 must be omitted.
    /**
     * The coefficients will be used directly in the computation (y[n] = sum(x[n-m+k]*b[k]) + sum(y[n-l+k]*a[k], k!=0) with m, l the order of b, a respectively)
     */
    void set_coefficients_out(std::vector<DataType> coefficients_out);
  };
}

#endif
