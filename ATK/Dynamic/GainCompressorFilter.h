/**
 * \file GainCompressorFilter.h
 */

#ifndef ATK_DYNAMIC_GAINCOMPRESSORFILTER_H
#define ATK_DYNAMIC_GAINCOMPRESSORFILTER_H

#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain "compressor". Computes a new amplitude/volume gain based on threshold, slope and the power of the input signal
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainCompressorFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    GainCompressorFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    ~GainCompressorFilter();
    
    void set_threshold(DataType_ threshold);
    void set_threshold_db(DataType_ threshold_db);
    DataType_ get_threshold() const;
    /**
     * 1:ratio is defined as the reduction factor. 1:1 is a reduction of 0, 1:2 is a reduction by a factor of 2...
     */
    void set_ratio(DataType_ ratio);
    DataType_ get_ratio() const;
    void set_softness(DataType_ softness);
    DataType_ get_softness() const;

  protected:
    virtual void process_impl(std::int64_t size) const override final;

    void recomputeLUT();
    
    DataType_ threshold;
    DataType_ ratio;
    DataType_ softness;
    size_t LUTsize;
    size_t LUTprecision;

    std::vector<DataType_> gainLUT;
  };
}

#endif
