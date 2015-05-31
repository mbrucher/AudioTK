/**
 * \file SD1ToneFilter.h
 */

#ifndef ATK_EQ_SD1TONEFILTERFILTER_H
#define ATK_EQ_SD1TONEFILTERFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class SD1ToneCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType R1, R2, R3, R4, C1, C2, C3, alpha;
    
    static const int in_order = 2;
    static const int out_order = 2;
    
    void setup() override;
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    SD1ToneCoefficients(int nb_channels = 1);
    
    void set_tone(DataType alpha);
    DataType get_tone() const;
  };
}

#endif
