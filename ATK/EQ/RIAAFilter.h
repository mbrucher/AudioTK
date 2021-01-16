/**
 * \file RIAAFilter.h
 * Filters for RIAA correction
 */

#ifndef ATK_EQ_RIAAFILTER_H
#define ATK_EQ_RIAAFILTER_H

#include <ATK/EQ/SecondOrderFilter.h>

#include <gsl/gsl>

namespace ATK
{
  /// RIAA coefficients used for RIAA correction
  template<typename DataType_>
  class RIAACoefficients : public SecondOrderCoreCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderCoreCoefficients<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::setup;
  protected:
    using Parent::in_order;
    using Parent::out_order;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;
        
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit RIAACoefficients(gsl::index nb_channels = 1);
  };

  /// RIAA coefficients used to create the inverse compensation (for mastering engineers)
  template<typename DataType_>
  class InverseRIAACoefficients : public SecondOrderCoreCoefficients<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = SecondOrderCoreCoefficients<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::setup;
  protected:
    using Parent::in_order;
    using Parent::out_order;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit InverseRIAACoefficients(gsl::index nb_channels = 1);
  };
}

#endif
