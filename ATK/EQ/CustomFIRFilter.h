/**
 * \file CustomFIRFilter.h
 */

#ifndef ATK_EQ_CUSTOMFIRFILTER_H
#define ATK_EQ_CUSTOMFIRFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class CustomFIRCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    int in_order;
    const static int out_order = 0;

    std::vector<DataType> coefficients_in;
    // There only to use IIRFilter, but won't actually be used, as out_order in always 0
    std::vector<DataType> coefficients_out;

  public:
    CustomFIRCoefficients(int nb_channels = 1);

    void set_coefficients_in(const std::vector<DataType>& coefficients_in);
  };
}

#endif
