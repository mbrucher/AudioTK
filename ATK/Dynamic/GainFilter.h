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
  /// Gain generic filter. Based on a LUT table, compute the gain.
  /*!
   * Be aware that the threshold is taken as a power measure contrary to the gain (there is a factor 2 in the dB computation)
   */
  template<typename DataType_>
  class ATK_DYNAMIC_EXPORT GainFilter : public TypedBaseFilter<DataType_>
  {
  protected:
    /// Simplify parent calls
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::converted_inputs_size;
    using Parent::outputs_size;
    using Parent::converted_inputs;
    using Parent::outputs;
    using Parent::nb_input_ports;
    using Parent::nb_output_ports;

  public:
    /*!
    * @brief Constructor
    * @param nb_channels is the number of input and output channels
    * @param LUTsize is the total LUT size used by the filter
    * @param LUTprecision is the number of elements used to compute values < 1
    */
    GainFilter(int nb_channels = 1, size_t LUTsize = 128*1024, size_t LUTprecision = 64);
    /// Destructor
    ~GainFilter();
    
    /// Sets the threashold (superior to 0)
    void set_threshold(DataType_ threshold);
    /// Sets the threashold in dB
    void set_threshold_db(DataType_ threshold_db);
    /// Returns the threashold
    DataType_ get_threshold() const;
    /// 1:ratio is defined as the reduction factor. 1:1 is a reduction of 0, 1:2 is a reduction by a factor of 2...
    void set_ratio(DataType_ ratio);
    /// Returns ratio
    DataType_ get_ratio() const;

  protected:
    virtual void process_impl(int64_t size) const override final;
    /// Computes the gain based on the LUT
    void process_impl_LUT(int64_t size) const;
    /// Computes the gain directly
    void process_impl_direct(int64_t size) const;

    /// Asks to recompute the LUT
    virtual void recomputeLUT();
    /// Called to compute the gain directly or when recomputing the LUT
    virtual DataType_ computeGain(DataType_ value) const = 0;
    
    /// Actually recomputes the LUT
    void start_recomputeLUT();

    /// Threshold
    DataType_ threshold;
    /// Ratio
    DataType_ ratio;

    /// Future used to track the thread recomputing the LUT
    std::future<void> recomputeFuture;
    /// Is the thread recomputing the LUT running (which way of computing the gain shall we use?)
    std::atomic<bool> isRunning;
    /// Indicates to start recomputing the LUT from the start, used when asked to change LUT paraemeters when the LUT is recomputed
    std::atomic<bool> resetRequest;
  private:
    size_t LUTsize;
    size_t LUTprecision;
    std::vector<DataType_> gainLUT;
  };
}

#endif
