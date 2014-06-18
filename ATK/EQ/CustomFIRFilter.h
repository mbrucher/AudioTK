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

    std::vector<DataType> coefficients_in;

  public:
    CustomFIRCoefficients(int nb_channels);

    void set_coefficients_in(const std::vector<DataType>& coefficients_in);
  };
}

#endif
