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
    CustomIIRCoefficients();

    void set_coefficients_in(const std::vector<DataType>& coefficients_in);
    void set_coefficients_out(const std::vector<DataType>& coefficients_out);
  };
}

#endif
