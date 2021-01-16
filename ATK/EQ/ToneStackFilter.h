/**
 * \file ToneStackFilter.h
 */

#ifndef ATK_EQ_TONESTACKFILTER_H
#define ATK_EQ_TONESTACKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename Coeffs>
  class IIRFilter;

  /// Emulation of a classic tone stack section of an amp
  template<typename DataType_>
  class ToneStackCoefficients: public TypedBaseFilter<DataType_>
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
    CoeffDataType R1{0};
    CoeffDataType R2{0};
    CoeffDataType R3{0};
    CoeffDataType R4{0};
    CoeffDataType C1{0};
    CoeffDataType C2{0};
    CoeffDataType C3{0};
    /// Parameters of the stack
    CoeffDataType low = 0.5;
    CoeffDataType middle = 0.5;
    CoeffDataType high = 0.5;
    
    static const gsl::index in_order = 3;
    static const gsl::index out_order = 3;
    
    void setup() override;
    
    /// MA part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_in;
    /// AR part of the filter, based on the electronic components specifications
    AlignedScalarVector coefficients_out;
    
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    explicit ToneStackCoefficients(gsl::index nb_channels = 1);
  public:
    /// Move constructor
    ToneStackCoefficients(ToneStackCoefficients&& other);

    /// Changes the low section parameter of the stack
    void set_low(CoeffDataType alpha);
    /// Gets the low tone parameter
    CoeffDataType get_low() const;
    /// Changes the middle section parameter of the stack
    void set_middle(CoeffDataType alpha);
    /// Gets the middle tone parameter
    CoeffDataType get_middle() const;
    /// Changes the high section parameter of the stack
    void set_high(CoeffDataType alpha);
    /// Gets the high tone parameter
    CoeffDataType get_high() const;
    
    /// Builds a Bassman stack equivalent filter (bass, Fender)
    static IIRFilter<ToneStackCoefficients<DataType_> > buildBassmanStack();
    /// Builds a JCM800 stack equivalent filter (guitar, Marshall)
    static IIRFilter<ToneStackCoefficients<DataType_> > buildJCM800Stack();

  protected:
  /// Sets the specific coefficients for a given stack
    void set_coefficients(CoeffDataType R1, CoeffDataType R2, CoeffDataType R3, CoeffDataType R4, CoeffDataType C1, CoeffDataType C2, CoeffDataType C3);
  };
}

#endif
