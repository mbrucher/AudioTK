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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    CoeffDataType R1;
    CoeffDataType R2;
    CoeffDataType R3;
    CoeffDataType R4;
    CoeffDataType C1;
    CoeffDataType C2;
    CoeffDataType C3;
    /// Parameter of the stack
    CoeffDataType alpha;
    
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
    SD1ToneCoefficients(gsl::index nb_channels = 1);
    
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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::AlignedScalarVector;
    using typename Parent::DataType;
    typedef typename TypeTraits<DataType>::Scalar CoeffDataType;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    CoeffDataType R1;
    CoeffDataType R2;
    CoeffDataType R3;
    CoeffDataType R4;
    CoeffDataType P;
    CoeffDataType C1;
    CoeffDataType C2;
    /// Parameter of the stack
    CoeffDataType alpha;
    
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
    TS9ToneCoefficients(gsl::index nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(CoeffDataType alpha);
    /// Returns the tone of the filter
    CoeffDataType get_tone() const;
  };
}

#endif
