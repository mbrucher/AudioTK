/**
 * \file ToneStackFilter.h
 */

#ifndef ATK_EQ_TONESTACKFILTER_H
#define ATK_EQ_TONESTACKFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class IIRFilter;

  template<typename DataType_>
  class ToneStackFilterCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType R1, R2, R3, R4, C1, C2, C3;
    DataType low, middle, high;
    
    static const int in_order = 3;
    static const int out_order = 3;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ToneStackFilterCoefficients(int nb_channels = 1);

    void set_low(DataType alpha);
    DataType get_low() const;
    void set_middle(DataType alpha);
    DataType get_middle() const;
    void set_high(DataType alpha);
    DataType get_high() const;
    
    static IIRFilter<ToneStackFilterCoefficients<DataType_> >* buildBassmanStack();
    static IIRFilter<ToneStackFilterCoefficients<DataType_> >* buildJCM800Stack();

  protected:
    void set_coefficients(DataType R1, DataType R2, DataType R3, DataType R4, DataType C1, DataType C2, DataType C3);
  };
}

#endif
