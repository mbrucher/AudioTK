/**
 * \file CustomFIRFilter.h
 */

#ifndef ATK_EQ_CUSTOMFIRFILTER_H
#define ATK_EQ_CUSTOMFIRFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Creates a custom FIR filter  when used as the coefficients class with FIRFilter
  template<typename DataType_>
  class CustomFIRCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using Parent::setup;

  protected:
    /// Order of the MA polynomial
    unsigned int in_order{0};

    /// MA polynomial
    AlignedScalarVector coefficients_in;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit CustomFIRCoefficients(gsl::index nb_channels = 1);

    /// Set custom coefficients for the FIR filter (usually called b in the literature). Be aware that coefficient for lag 0 is the last of this vector (reverse order)
    void set_coefficients_in(const std::vector<typename TypeTraits<DataType>::Scalar>& coefficients_in);
  };
}

#endif
