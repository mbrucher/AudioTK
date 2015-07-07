/**
 * \file GainFilter.h
 */

#ifndef ATK_DYNAMIC_GAINFILTER_H
#define ATK_DYNAMIC_GAINFILTER_H

#include <atomic>
#include <future>
#include <vector>

#include <ATK/Core/TypedBaseFilter.h>
#include "config.h"

namespace ATK
{
  /**
   * Gain generic filter. Based on a LUT table, compute the gain.
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainFilter : public TypedBaseFilter<DataType_>
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
    GainFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    ~GainFilter();
    
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
    virtual void process_impl(int64_t size) const override final;
    void process_impl_LUT(int64_t size) const;
    void process_impl_direct(int64_t size) const;

    virtual void recomputeLUT() = 0;
    virtual DataType_ computeGain(DataType_ value) const = 0;
    
    void start_recomputeLUT();

    DataType_ threshold;
    DataType_ ratio;
    DataType_ softness;
    size_t LUTsize;
    size_t LUTprecision;

    std::vector<DataType_> gainLUT;

    std::future<void> recomputeFuture;
    bool resetRequest;
  };
}

#endif
