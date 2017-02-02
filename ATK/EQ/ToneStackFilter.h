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
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    DataType R1, R2, R3, R4, C1, C2, C3;
    /// Parameters of the stack
    DataType low, middle, high;
    
    static const int in_order = 3;
    static const int out_order = 3;
    
    void setup() override;
    
    /// MA part of the filter, based on the electronic components specifications
    AlignedVector coefficients_in;
    /// AR part of the filter, based on the electronic components specifications
    AlignedVector coefficients_out;
    
    /*!
     * @brief Constructor
     * @param nb_channels is the number of input and output channels
     */
    ToneStackCoefficients(int nb_channels = 1);
  public:
    /// Move constructor
    ToneStackCoefficients(ToneStackCoefficients&& other);

    /// Changes the low section parameter of the stack
    void set_low(DataType_ alpha);
    /// Gets the low tone parameter
    DataType_ get_low() const;
    /// Changes the middle section parameter of the stack
    void set_middle(DataType_ alpha);
    /// Gets the middle tone parameter
    DataType_ get_middle() const;
    /// Changes the high section parameter of the stack
    void set_high(DataType_ alpha);
    /// Gets the high tone parameter
    DataType_ get_high() const;
    
    /// Builds a Bassman stack equivalent filter (bass, Fender)
    static IIRFilter<ToneStackCoefficients<DataType_> > buildBassmanStack();
    /// Builds a JCM800 stack equivalent filter (guitar, Marshall)
    static IIRFilter<ToneStackCoefficients<DataType_> > buildJCM800Stack();

  protected:
  /// Sets the specific coefficients for a given stack
    void set_coefficients(DataType R1, DataType R2, DataType R3, DataType R4, DataType C1, DataType C2, DataType C3);
  };
}

#endif
