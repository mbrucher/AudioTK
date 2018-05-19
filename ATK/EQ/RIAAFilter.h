/**
 * \file RIAAFilter.h
 * Filters for RIAA correction
 */

#ifndef ATK_EQ_RIAAFILTER_H
#define ATK_EQ_RIAAFILTER_H

#include <gsl/gsl>

#include <ATK/EQ/FourthOrderFilter.h>
#include <ATK/EQ/SecondOrderFilter.h>

namespace ATK
{
  /// RIAA coefficients used for RIAA correction
  template<typename DataType_>
  class RIAACoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::setup;
  protected:
    const static gsl::index in_order;
    const static gsl::index out_order;
    AlignedScalarVector coefficients_in;
    AlignedScalarVector coefficients_out;
    
    void setup() override;
        
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    RIAACoefficients(gsl::index nb_channels = 1);
  };

  /// RIAA coefficients used to create the inverse compensation (for mastering engineers)
  template<typename DataType_>
  class InverseRIAACoefficients : public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
    using Parent::setup;
  protected:
    const static gsl::index in_order;
    const static gsl::index out_order;
    AlignedScalarVector coefficients_in;
    AlignedScalarVector coefficients_out;

    void setup() override;

  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    InverseRIAACoefficients(gsl::index nb_channels = 1);
  };
}

#endif
