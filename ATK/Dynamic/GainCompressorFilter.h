/**
 * \file GainCompressorFilter.h
 */

#ifndef ATK_DYNAMIC_GAINCOMPRESSORFILTER_H
#define ATK_DYNAMIC_GAINCOMPRESSORFILTER_H

#include <vector>

#include <ATK/Dynamic/GainFilter.h>
#include "config.h"

namespace ATK
{
  /// Gain "compressor". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainCompressorFilter : public GainFilter<DataType_>
  {
  protected:
    typedef GainFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::ratio;
    using Parent::recomputeFuture;
    using Parent::recomputeLUT;
    using Parent::start_recomputeLUT;

    DataType_ softness;
  public:
    GainCompressorFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    ~GainCompressorFilter();

    void set_softness(DataType_ softness);
    DataType_ get_softness() const;

  protected:
    DataType_ computeGain(DataType_ value) const override final;
  };
}

#endif
