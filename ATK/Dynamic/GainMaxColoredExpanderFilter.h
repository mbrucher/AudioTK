/**
 * \file GainMaxColoredExpanderFilter.h
 */

#ifndef ATK_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER_H
#define ATK_DYNAMIC_GAINMAXCOLOREDEXPANDERFILTER_H

#include <vector>

#include <ATK/Dynamic/GainFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain "expander". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
   * The maximum reduction is given by max_reduction
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainMaxColoredExpanderFilter : public GainFilter<DataType_>
  {
  protected:
    typedef GainFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::ratio;
    using Parent::recomputeFuture;
    using Parent::recomputeLUT;
    using Parent::start_recomputeLUT;

    DataType_ softness;
    DataType_ max_reduction;
    DataType_ color;
    DataType_ quality;

  public:
    GainMaxColoredExpanderFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 1024);
    ~GainMaxColoredExpanderFilter();

    void set_softness(DataType_ softness);
    DataType_ get_softness() const;
    
    void set_max_reduction(DataType_ max_reduction);
    void set_max_reduction_db(DataType_ max_reduction);
    DataType_ get_max_reduction() const;

    void set_color(DataType_ color);
    DataType_ get_color() const;
    void set_quality(DataType_ quality);
    DataType_ get_quality() const;

  protected:
    DataType_ computeGain(DataType_ value) const override final;
  };
}

#endif
