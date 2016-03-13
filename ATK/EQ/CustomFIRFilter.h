/**
 * \file CustomFIRFilter.h
 */

#ifndef ATK_EQ_CUSTOMFIRFILTER_H
#define ATK_EQ_CUSTOMFIRFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Creates a custom FIR filter  when used as the coefficients class with IIRFilter
  template<typename DataType_>
  class CustomFIRCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::setup;
  protected:
    /// Order of the MA polynome
    int in_order;
    /// Set to 0 so IIRFilter understand that it can bypass the AR section
    const static int out_order = 0;

    /// MA polynome
    std::vector<DataType> coefficients_in;
    /// There only to use IIRFilter, but won't actually be used, as out_order in always 0
    std::vector<DataType> coefficients_out;

  public:
    CustomFIRCoefficients(int nb_channels = 1);

    /// Set custom coefficients for the FIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
    void set_coefficients_in(std::vector<DataType> coefficients_in);
  };
}

#endif
