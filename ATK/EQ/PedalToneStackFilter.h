/**
 * \file PedalToneStackFilter.h
 */

#ifndef ATK_EQ_PEDALTONESTACKFILTER_H
#define ATK_EQ_PEDALTONESTACKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  /// Emulation of the SD1 tone section
  template<typename DataType_>
  class SD1ToneCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    CoeffDataType R1 = 10e3;
    CoeffDataType R2 = 22e3;
    CoeffDataType R3 = 470;
    CoeffDataType R4 = 10e3;
    CoeffDataType C1 = 0.018e-6;
    CoeffDataType C2 = 0.027e-6;
    CoeffDataType C3 = 0.01e-6;
    /// Parameter of the stack
    CoeffDataType alpha{1};
    
    static const gsl::index in_order = 2;
    static const gsl::index out_order = 2;

    void setup() override;
    
    /// MA part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_in;
    /// AR part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit SD1ToneCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(CoeffDataType alpha);
    /// Returns the tone of the filter
    CoeffDataType get_tone() const;
  };

  /// Emulation of the TS9 tone section
  template<typename DataType_>
  class TS9ToneCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    /// Simplify parent calls
    using Parent = TypedBaseFilter<DataType_>;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    using CoeffDataType = typename TypeTraits<DataType>::Scalar;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    CoeffDataType R1 = 1e3;
    CoeffDataType R2 = 10e3;
    CoeffDataType R3 = 1e3;
    CoeffDataType R4 = 220;
    CoeffDataType P = 22e3;
    CoeffDataType C1 = 0.022e-6;
    CoeffDataType C2 = 0.022e-6;
    /// Parameter of the stack
    CoeffDataType alpha = 0.5;

    static const gsl::index in_order = 2;
    static const gsl::index out_order = 2;
    
    void setup() override;
    
    /// MA part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_in;
    /// AR part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_out;
    
  public:
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit TS9ToneCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(CoeffDataType alpha);
    /// Returns the tone of the filter
    CoeffDataType get_tone() const;
  };
}

#endif
