/**
 * \file LinkwitzRileyFilter.h
 */

#ifndef ATK_EQ_LINKWITZRILEYFILTER_H
#define ATK_EQ_LINKWITZRILEYFILTER_H

#include <ATK/EQ/SecondOrderFilter.h>

namespace ATK
{
  template<typename DataType_>
  class LinkwitzRileyLowPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;
        
  public:
    LinkwitzRileyLowPassCoefficients(int nb_channels = 1);
  };

  template<typename DataType_>
  class LinkwitzRileyHighPassCoefficients : public BaseSecondOrderCoefficients<DataType_>
  {
  public:
    typedef BaseSecondOrderCoefficients<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
    using Parent::output_sampling_rate;
  protected:
    using Parent::cut_frequency;
    using Parent::coefficients_in;
    using Parent::coefficients_out;

    void setup() override;

  public:
    LinkwitzRileyHighPassCoefficients(int nb_channels = 1);
  };
}

#endif
