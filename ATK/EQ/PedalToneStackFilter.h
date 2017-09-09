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
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    DataType R1, R2, R3, R4, C1, C2, C3;
    /// Parameter of the stack
    DataType alpha;
    
    static const int in_order = 2;
    static const int out_order = 2;
    
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
    SD1ToneCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(DataType_ alpha);
    /// Returns the tone of the filter
    DataType_ get_tone() const;
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
    using Parent::input_sampling_rate;
  protected:
    /// Electronic components of the stack
    DataType R1, R2, R3, R4, P, C1, C2;
    /// Parameter of the stack
    DataType alpha;
    
    static const int in_order = 2;
    static const int out_order = 2;
    
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
    TS9ToneCoefficients(std::size_t nb_channels = 1);
    
    /// Sets the tone of the filter
    void set_tone(DataType_ alpha);
    /// Returns the tone of the filter
    DataType_ get_tone() const;
  };
}

#endif
