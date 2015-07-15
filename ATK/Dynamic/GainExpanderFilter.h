/**
 * \file GainExpanderFilter.h
 */

#ifndef ATK_DYNAMIC_GAINEXPANDERFILTER_H
#define ATK_DYNAMIC_GAINEXPANDERFILTER_H

#include <vector>

#include <ATK/Dynamic/GainFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain "expander". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainExpanderFilter : public GainFilter<DataType_>
  {
  protected:
    typedef GainFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::ratio;
    using Parent::softness;
    using Parent::recomputeFuture;
    using Parent::recomputeLUT;

  public:
    GainExpanderFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 1024);
    ~GainExpanderFilter();

  protected:
    DataType_ computeGain(DataType_ value) const override final;
  };
}

#endif
